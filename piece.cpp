#include "piece.h"

carrompiece_t::carrompiece_t()
{
  pos.x = 5.0;
  pos.y = 5.0;
  vel.dx = 0.0;
  vel.dy = 0.0;
  type = WHITE;
  is_visible = true;
}

