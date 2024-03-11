#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#define WIDTH 800
#define HEIGHT 800

#define BLOCK_LEN (HEIGHT / 8.0)

#define WHITE_SQUARE_COLOR ((Color){238, 216, 192, 255})
#define BLACK_SQUARE_COLOR ((Color){171, 122, 101, 255})

typedef struct {
} GameState;

void GameCleanup(void);
void GameInit(void);
void GameUpdate(void);
void GameDraw(void);

#endif // GAME_H
