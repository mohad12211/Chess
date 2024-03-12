#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#define WIDTH 720
#define HEIGHT 720

#define BLOCK_LEN (HEIGHT / 8.0)

#define WHITE_SQUARE_COLOR ((Color){238, 216, 192, 255})
#define BLACK_SQUARE_COLOR ((Color){171, 122, 101, 255})

typedef struct {
  Texture2D pieces;
  int board[64];
  int selected;
} GameState;

void GameCleanup(void);
void GameInit(void);
void GameUpdate(void);
void GameDraw(void);

#endif // GAME_H
