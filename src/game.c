#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "move.h"
#include "network.h"
#include "piece.h"
#include "util.h"

static GameState state = {0};
static void CalculateLegalMoves(void);

void GameCleanup(void) { UnloadTexture(state.pieces); }

void GameInit(void) {
  Image pieces_imgage = LoadImage("assets/pieces.png");
  Texture2D pieces = LoadTextureFromImage(pieces_imgage);
  UnloadImage(pieces_imgage);
  state.pieces = pieces;

  state.selected = -1;
  state.turn = White;

  state.sockfd = ConnectionToServer();
  state.color = GetColorFromServer(state.sockfd);

  if (state.color == Black) {
    state.board[0].type = Rook | White;
    state.board[1].type = Knight | White;
    state.board[2].type = Bishop | White;
    state.board[3].type = King | White;
    state.board[4].type = Queen | White;
    state.board[5].type = Bishop | White;
    state.board[6].type = Knight | White;
    state.board[7].type = Rook | White;
    state.board[8].type = Pawn | White;
    state.board[9].type = Pawn | White;
    state.board[10].type = Pawn | White;
    state.board[11].type = Pawn | White;
    state.board[12].type = Pawn | White;
    state.board[13].type = Pawn | White;
    state.board[14].type = Pawn | White;
    state.board[15].type = Pawn | White;

    state.board[48].type = Pawn | Black;
    state.board[49].type = Pawn | Black;
    state.board[50].type = Pawn | Black;
    state.board[51].type = Pawn | Black;
    state.board[52].type = Pawn | Black;
    state.board[53].type = Pawn | Black;
    state.board[54].type = Pawn | Black;
    state.board[55].type = Pawn | Black;

    state.board[56].type = Rook | Black;
    state.board[57].type = Knight | Black;
    state.board[58].type = Bishop | Black;
    state.board[59].type = King | Black;
    state.board[60].type = Queen | Black;
    state.board[61].type = Bishop | Black;
    state.board[62].type = Knight | Black;
    state.board[63].type = Rook | Black;
  } else {
    state.board[0].type = Rook | Black;
    state.board[1].type = Knight | Black;
    state.board[2].type = Bishop | Black;
    state.board[3].type = Queen | Black;
    state.board[4].type = King | Black;
    state.board[5].type = Bishop | Black;
    state.board[6].type = Knight | Black;
    state.board[7].type = Rook | Black;

    state.board[8].type = Pawn | Black;
    state.board[9].type = Pawn | Black;
    state.board[10].type = Pawn | Black;
    state.board[11].type = Pawn | Black;
    state.board[12].type = Pawn | Black;
    state.board[13].type = Pawn | Black;
    state.board[14].type = Pawn | Black;
    state.board[15].type = Pawn | Black;

    state.board[48].type = Pawn | White;
    state.board[49].type = Pawn | White;
    state.board[50].type = Pawn | White;
    state.board[51].type = Pawn | White;
    state.board[52].type = Pawn | White;
    state.board[53].type = Pawn | White;
    state.board[54].type = Pawn | White;
    state.board[55].type = Pawn | White;

    state.board[56].type = Rook | White;
    state.board[57].type = Knight | White;
    state.board[58].type = Bishop | White;
    state.board[59].type = Queen | White;
    state.board[60].type = King | White;
    state.board[61].type = Bishop | White;
    state.board[62].type = Knight | White;
    state.board[63].type = Rook | White;
  }

  CalculateLegalMoves();
}

void GameUpdate(void) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    int start = VectorToIndex(Vector2Scale(GetMousePosition(), 1.0 / BLOCK_LEN));

    if (GET_COLOR(state.board[start].type) == GET_COLOR(state.color) && state.turn == state.color) {
      state.selected = start;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && state.selected != -1) {
    int end = VectorToIndex(Vector2Scale(GetMousePosition(), 1.0 / BLOCK_LEN));
    Move move = {state.selected, end};

    if (move.start != move.end) {
      for (size_t i = 0; i < state.board[state.selected].legalMoves.len; i++) {
        if (MoveIsEqual(state.board[state.selected].legalMoves.moves[i], move)) {
          SendMoveToServer(state.sockfd, move);
          state.lastMove = move;
          VecFree(&state.board[move.end].legalMoves);
          state.board[move.end] = state.board[move.start];
          state.board[move.end].hasMoved = true;
          state.board[move.start].type = None;
          state.turn = INVERT_COLOR(state.turn);
          break;
        }
      }
    }

    state.selected = -1;
  }

  Move move = ReceiveMoveFromServer(state.sockfd);
  if (!MoveIsNull(move)) {
    VecFree(&state.board[move.end].legalMoves);
    state.board[move.end] = state.board[move.start];
    state.board[move.start].type = None;
    state.turn = INVERT_COLOR(state.turn);
    state.lastMove = move;
    CalculateLegalMoves();
  }
}

void GameDraw(void) {
  BeginDrawing();
  ClearBackground(BLACK);

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      Color color = (row + col) % 2 == 0 ? WHITE_SQUARE_COLOR : BLACK_SQUARE_COLOR;
      DrawRectangle(col * BLOCK_LEN, row * BLOCK_LEN, BLOCK_LEN, BLOCK_LEN, color);
    }
  }

  if (!MoveIsNull(state.lastMove)) {
    DrawRectangleV(Vector2Scale(IndexToVector(state.lastMove.start), BLOCK_LEN), BLOCK_VECTOR, MOVE_COLOR);
    DrawRectangleV(Vector2Scale(IndexToVector(state.lastMove.end), BLOCK_LEN), BLOCK_VECTOR, MOVE_COLOR);
  }

  if (state.selected != -1) {
    Piece *piece = &state.board[state.selected];

    for (size_t j = 0; j < piece->legalMoves.len; j++) {
      DrawRectangleV(Vector2Scale(IndexToVector(piece->legalMoves.moves[j].end), BLOCK_LEN), BLOCK_VECTOR, LEGAL_MOVE_COLOR);
    }
  }

  for (int i = 0; i < 64; i++) {
    if (i == state.selected) {
      continue;
    }
    PieceType piece = state.board[i].type;
    PieceDraw(piece, Vector2Scale(IndexToVector(i), BLOCK_LEN), state.pieces);
  }

  PieceType piece = state.board[state.selected].type;
  Vector2 position = {GetMouseX() - BLOCK_LEN / 2.0, GetMouseY() - BLOCK_LEN / 2.0};
  PieceDraw(piece, position, state.pieces);

  DrawFPS(5, 5);
  EndDrawing();
}

static void CalculateLegalMoves(void) {
  for (int i = 0; i < 64; i++) {
    Piece *piece = &state.board[i];
    VecClear(&piece->legalMoves);

    if (GET_COLOR(piece->type) != GET_COLOR(state.color)) {
      continue;
    }

    Vector2 start = IndexToVector(i);
    switch (GET_TYPE(piece->type)) {
    case King: {
      for (int dir = 0; dir < DirectionCount; dir++) {
        Vector2 end = GetVectorInDirection(start, dir);
        if (!Vector2Equals(end, start) && GET_COLOR(state.board[VectorToIndex(end)].type) != GET_COLOR(state.color)) {
          VecPush(&piece->legalMoves, ((Move){i, VectorToIndex(end)}));
        }
      }
      break;
    }
    case Queen:
      break;
    case Bishop:
      break;
    case Knight:
      break;
    case Rook:
      break;
    case Pawn: {
      Vector2 end = GetVectorInDirection(start, NE);
      int endIndex = VectorToIndex(end);
      if (state.board[endIndex].type != None && GET_COLOR(state.board[endIndex].type) != GET_COLOR(state.color)) {
        VecPush(&piece->legalMoves, ((Move){i, endIndex}));
      }

      end = GetVectorInDirection(IndexToVector(i), NW);
      endIndex = VectorToIndex(end);
      if (state.board[endIndex].type != None && GET_COLOR(state.board[endIndex].type) != GET_COLOR(state.color)) {
        VecPush(&piece->legalMoves, ((Move){i, endIndex}));
      }

      end = GetVectorInDirection(start, N);
      endIndex = VectorToIndex(end);
      if (state.board[endIndex].type == 0) {
        VecPush(&piece->legalMoves, ((Move){i, endIndex}));
      }

      if (!piece->hasMoved) {
        end = GetVectorInDirection(end, N);
        if (state.board[VectorToIndex(end)].type == 0) {
          VecPush(&piece->legalMoves, ((Move){i, VectorToIndex(end)}));
        }
      }

      break;
    }
    }
  }
}
