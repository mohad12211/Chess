#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>

typedef struct {
  char from;
  char to;
} Move;

bool MoveIsNull(Move move);

#endif // MOVE_H
