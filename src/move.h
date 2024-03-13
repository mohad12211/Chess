#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>

typedef struct {
  int start;
  int end;
} Move;

bool MoveIsNull(Move move);

#endif // MOVE_H
