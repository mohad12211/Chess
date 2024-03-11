#include <raylib.h>
#include <raymath.h>

#include "game.h"
#include "piece.h"

void PieceDraw(const int piece, const Vector2 position, Texture2D pieces) {
  int type = GET_TYPE(piece);
  int color = GET_COLOR(piece);

  if (type == -1 || color == -1)
    return;

  Rectangle source = {type * BLOCK_LEN, color * BLOCK_LEN, BLOCK_LEN, BLOCK_LEN};
  DrawTextureRec(pieces, source, Vector2Scale(position, BLOCK_LEN), WHITE);
}
