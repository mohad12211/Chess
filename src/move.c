#include <stdbool.h>

#include "move.h"

bool MoveIsNull(Move move) { return move.start == 0 && move.end == 0; }
