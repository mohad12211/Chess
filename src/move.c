#include <stdbool.h>

#include "move.h"

bool MoveIsNull(Move move) { return move.from == 0 && move.to == 0; }
