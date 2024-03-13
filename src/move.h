#ifndef MOVE_H
#define MOVE_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
  int start;
  int end;
} Move;

bool MoveIsNull(Move move);
Vector2 MoveStartVector(Move move);
Vector2 MoveEndVector(Move move);

#endif // MOVE_H
