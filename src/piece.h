#ifndef PIECE_H
#define PIECE_H

#include <raylib.h>

typedef enum {
  None = 0,
  King = 1,
  Queen = 2,
  Bishop = 3,
  Knight = 4,
  Rook = 5,
  Pawn = 6,
  White = 8,
  Black = 16,
} Piece;

#define GET_TYPE(piece) ((piece & 7) - 1)
#define GET_COLOR(piece) ((piece >> 3) - 1)
#define INVERT_COLOR(color) (24 ^ color)

void PieceDraw(const int piece, const Vector2 position, Texture2D pieces);

#endif // PIECE_H
