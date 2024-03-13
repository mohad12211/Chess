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

#define VecPush(xs, x)                                                                                                                                         \
  do {                                                                                                                                                         \
    if ((xs)->len >= (xs)->capacity) {                                                                                                                         \
      if ((xs)->capacity == 0)                                                                                                                                 \
        (xs)->capacity = 256;                                                                                                                                  \
      else                                                                                                                                                     \
        (xs)->capacity *= 2;                                                                                                                                   \
      (xs)->moves = realloc((xs)->moves, (xs)->capacity * sizeof(*(xs)->moves));                                                                               \
    }                                                                                                                                                          \
                                                                                                                                                               \
    (xs)->moves[(xs)->len++] = (x);                                                                                                                            \
  } while (0)

#define VecFree(xs)                                                                                                                                            \
  do {                                                                                                                                                         \
    free((xs)->moves);                                                                                                                                         \
    (xs)->len = 0;                                                                                                                                             \
    (xs)->capacity = 0;                                                                                                                                        \
  } while (0)

#define VecClear(xs)                                                                                                                                           \
  do {                                                                                                                                                         \
    (xs)->len = 0;                                                                                                                                             \
  } while (0)

typedef enum { N, E, S, W, NE, SE, SW, NW, DirectionCount } Direction;

bool MoveIsNull(Move move);
bool MoveIsEqual(Move m1, Move m2);
Vector2 GetVectorInDirection(Vector2 vector, Direction direction);

#endif // MOVE_H
