#include <raylib.h>
#include <raymath.h>

#include "game.h"
#include "piece.h"

void PieceDraw(const PieceType piece, const Vector2 position, Texture2D pieces) {
  int type = GET_TYPE(piece);
  int color = GET_COLOR(piece);

  if (type == 0 || color == 0)
    return;

  Rectangle source = {(type - 1) * BLOCK_LEN, (color - 1) * BLOCK_LEN, BLOCK_LEN, BLOCK_LEN};
  DrawTextureRec(pieces, source, position, WHITE);
}
