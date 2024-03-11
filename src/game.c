#include <raylib.h>

#include "game.h"

static GameState state = {0};

void GameCleanup(void) { UnloadTexture(state.pieces); }

void GameInit(void) {
  Image pieces_imgage = LoadImage("assets/pieces.png");
  Texture2D pieces = LoadTextureFromImage(pieces_imgage);
  UnloadImage(pieces_imgage);
  state.pieces = pieces;
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
  Rectangle source = {1 * BLOCK_LEN, BLOCK_LEN, BLOCK_LEN, BLOCK_LEN};
  DrawTextureRec(state.pieces, source, (Vector2){0, 0}, WHITE);

  EndDrawing();
}
