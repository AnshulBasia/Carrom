#pragma once

#include "piece.h"
#include "gamestate.h"

class renderstate_t 
{
  private:
    carrompiece_t p1, p[20];
    
    void draw_coin(carrompiece_t& piece);
    void draw_board();
    
  public:
    void render();
    void copy_state();
};

