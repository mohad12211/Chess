#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#include "game.h"
#include "move.h"
#include "network.h"
#include "piece.h"
#include "util.h"

static GameState state = {0};

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
    state.board[0] = Rook | White;
    state.board[1] = Knight | White;
    state.board[2] = Bishop | White;
    state.board[3] = King | White;
    state.board[4] = Queen | White;
    state.board[5] = Bishop | White;
    state.board[6] = Knight | White;
    state.board[7] = Rook | White;
    state.board[8] = Pawn | White;
    state.board[9] = Pawn | White;
    state.board[10] = Pawn | White;
    state.board[11] = Pawn | White;
    state.board[12] = Pawn | White;
    state.board[13] = Pawn | White;
    state.board[14] = Pawn | White;
    state.board[15] = Pawn | White;

    state.board[48] = Pawn | Black;
    state.board[49] = Pawn | Black;
    state.board[50] = Pawn | Black;
    state.board[51] = Pawn | Black;
    state.board[52] = Pawn | Black;
    state.board[53] = Pawn | Black;
    state.board[54] = Pawn | Black;
    state.board[55] = Pawn | Black;

    state.board[56] = Rook | Black;
    state.board[57] = Knight | Black;
    state.board[58] = Bishop | Black;
    state.board[59] = King | Black;
    state.board[60] = Queen | Black;
    state.board[61] = Bishop | Black;
    state.board[62] = Knight | Black;
    state.board[63] = Rook | Black;
  } else {
    state.board[0] = Rook | Black;
    state.board[1] = Knight | Black;
    state.board[2] = Bishop | Black;
    state.board[3] = Queen | Black;
    state.board[4] = King | Black;
    state.board[5] = Bishop | Black;
    state.board[6] = Knight | Black;
    state.board[7] = Rook | Black;

    state.board[8] = Pawn | Black;
    state.board[9] = Pawn | Black;
    state.board[10] = Pawn | Black;
    state.board[11] = Pawn | Black;
    state.board[12] = Pawn | Black;
    state.board[13] = Pawn | Black;
    state.board[14] = Pawn | Black;
    state.board[15] = Pawn | Black;

    state.board[48] = Pawn | White;
    state.board[49] = Pawn | White;
    state.board[50] = Pawn | White;
    state.board[51] = Pawn | White;
    state.board[52] = Pawn | White;
    state.board[53] = Pawn | White;
    state.board[54] = Pawn | White;
    state.board[55] = Pawn | White;

    state.board[56] = Rook | White;
    state.board[57] = Knight | White;
    state.board[58] = Bishop | White;
    state.board[59] = Queen | White;
    state.board[60] = King | White;
    state.board[61] = Bishop | White;
    state.board[62] = Knight | White;
    state.board[63] = Rook | White;
  }
}

void GameUpdate(void) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    int start = VectorToIndex(Vector2Scale(GetMousePosition(), 1.0 / BLOCK_LEN));

    if (GET_COLOR(state.board[start]) == GET_COLOR(state.color) && state.turn == state.color) {
      state.selected = start;
    }
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && state.selected != -1) {
    int end = VectorToIndex(Vector2Scale(GetMousePosition(), 1.0 / BLOCK_LEN));
    Move move = {state.selected, end};
    state.selected = -1;

    if (move.start != move.end) {
      SendMoveToServer(state.sockfd, move);
      state.lastMove = move;
      state.board[move.end] = state.board[move.start];
      state.board[move.start] = None;
      state.turn = INVERT_COLOR(state.turn);
    }
  }

  Move move = ReceiveMoveFromServer(state.sockfd);
  if (!MoveIsNull(move)) {
    state.board[move.end] = state.board[move.start];
    state.board[move.start] = 0;
    state.turn = INVERT_COLOR(state.turn);
    state.lastMove = move;
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

  for (int i = 0; i < 64; i++) {
    if (i == state.selected) {
      continue;
    }
    int piece = state.board[i];
    PieceDraw(piece, Vector2Scale(IndexToVector(i), BLOCK_LEN), state.pieces);
  }

  int piece = state.board[state.selected];
  Vector2 position = {GetMouseX() - BLOCK_LEN / 2.0, GetMouseY() - BLOCK_LEN / 2.0};
  PieceDraw(piece, position, state.pieces);

  DrawFPS(5, 5);
  EndDrawing();
}
