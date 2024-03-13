#ifndef MOVE_H
#define MOVE_H

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int start;
  int end;
} Move;

typedef struct {
  Move *moves;
  size_t len;
  size_t capacity;
} MoveVec;

typedef enum { N, E, S, W, NE, SE, SW, NW, DirectionCount } Direction;

bool MoveIsNull(Move move);
Vector2 GetVectorInDirection(Vector2 vector, Direction direction);

#endif // MOVE_H
