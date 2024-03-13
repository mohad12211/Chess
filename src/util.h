#ifndef UTIL_H
#define UTIL_H

#include <raylib.h>

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

Vector2 IndexToVector(int index);
int VectorToIndex(Vector2 vector);

#endif // UTIL_H
