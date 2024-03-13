#include <stdbool.h>

#include "move.h"

bool MoveIsNull(Move move) { return move.start == 0 && move.end == 0; }

bool MoveIsEqual(Move m1, Move m2) { return m1.start == m2.start && m1.end == m2.end; }

Vector2 GetVectorInDirection(Vector2 vector, Direction direction) {
  Vector2 result = vector;
  switch (direction) {
  case N:
    if (vector.y > 0) {
      result.y--;
    }
    break;
  case E:
    if (vector.x < 7) {
      result.x++;
    }
    break;
  case S:
    if (vector.y < 7) {
      result.y++;
    }
    break;
  case W:
    if (vector.x > 0) {
      result.x--;
    }
    break;
  case NE:
    if (vector.y > 0 && vector.x < 7) {
      result.y--;
      result.x++;
    }
    break;
  case SE:
    if (vector.y < 7 && vector.x < 7) {
      result.y++;
      result.x++;
    }
    break;
  case SW:
    if (vector.y < 7 && vector.x > 0) {
      result.y++;
      result.x--;
    }
    break;
  case NW:
    if (vector.y > 0 && vector.x > 0) {
      result.y--;
      result.x--;
    }
    break;
  case DirectionCount:
    break;
  }
  return result;
}
