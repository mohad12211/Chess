#include <raylib.h>

#include "util.h"

Vector2 IndexToVector(int index) { return (Vector2){(index % 8), (int)(index / 8)}; }
