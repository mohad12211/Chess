#include <raylib.h>

#include "game.h"

void GameCleanup(void) {}

void GameInit(void) {}

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

  EndDrawing();
}
