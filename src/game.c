#include <raylib.h>

#include "game.h"
#include "piece.h"

static GameState state = {0};

void GameCleanup(void) { UnloadTexture(state.pieces); }

void GameInit(void) {
  Image pieces_imgage = LoadImage("assets/pieces.png");
  Texture2D pieces = LoadTextureFromImage(pieces_imgage);
  UnloadImage(pieces_imgage);

  state.pieces = pieces;
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

void GameUpdate(void) {}

void GameDraw(void) {
  BeginDrawing();
  ClearBackground(BLACK);

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      Color color = (row + col) % 2 == 0 ? WHITE_SQUARE_COLOR : BLACK_SQUARE_COLOR;
      DrawRectangle(col * BLOCK_LEN, row * BLOCK_LEN, BLOCK_LEN, BLOCK_LEN, color);
    }
  }

  for (int i = 0; i < 64; i++) {
    int piece = state.board[i];
    Vector2 position = {i % 8, (int)(i / 8)};
    PieceDraw(piece, position, state.pieces);
  }

  EndDrawing();
}
