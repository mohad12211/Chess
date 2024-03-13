#include <raylib.h>

#include "util.h"

Vector2 IndexToVector(int index) { return (Vector2){(index % 8), (int)(index / 8)}; }
int VectorToIndex(Vector2 vector) { return (int)vector.y * 8 + (int)vector.x; }
