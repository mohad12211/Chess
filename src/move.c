#include <stdbool.h>

#include "move.h"

bool MoveIsNull(Move move) { return move.start == 0 && move.end == 0; }

bool MoveIsEqual(Move m1, Move m2) { return m1.start == m2.start && m1.end == m2.end; }

Vector2 GetVectorInDirection(Vector2 vector, Direction direction) {
  Vector2 result = vector;
  switch (direction) {
  case N:
    result.y--;
    break;
  case E:
    result.x++;
    break;
  case S:
    result.y++;
    break;
  case W:
    result.x--;
    break;
  case NE:
    result.y--;
    result.x++;
    break;
  case SE:
    result.y++;
    result.x++;
    break;
  case SW:
    result.y++;
    result.x--;
    break;
  case NW:
    result.y--;
    result.x--;
    break;
  case K1:
    result.y -= 2;
    result.x++;
    break;
  case K2:
    result.y--;
    result.x += 2;
    break;
  case K4:
    result.x += 2;
    result.y++;
    break;
  case K5:
    result.x++;
    result.y += 2;
    break;
  case K7:
    result.y += 2;
    result.x--;
    break;
  case K8:
    result.y++;
    result.x -= 2;
    break;
  case K10:
    result.x -= 2;
    result.y--;
    break;
  case K11:
    result.y -= 2;
    result.x--;
    break;
  }

  if (result.x >= 0 && result.x <= 7 && result.y >= 0 && result.y <= 7) {
    return result;
  }
  return vector;
}
