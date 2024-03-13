#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdbool.h>

#include "move.h"

#define WIDTH 720
#define HEIGHT 720

#define BLOCK_LEN (HEIGHT / 8.0)

#define WHITE_SQUARE_COLOR ((Color){238, 216, 192, 255})
#define BLACK_SQUARE_COLOR ((Color){171, 122, 101, 255})
#define MOVE_COLOR ((Color){207, 172, 106, 255})

typedef struct {
  Texture2D pieces;
  int board[64];
  int selected;
  int sockfd;
  int turn;
  int color;
  Move lastMove;
} GameState;

void GameCleanup(void);
void GameInit(void);
void GameUpdate(void);
void GameDraw(void);

#endif // GAME_H
