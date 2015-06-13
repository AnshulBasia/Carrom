#pragma once

#include "piece.h"
#include "renderstate.h"

class gamestate_t 
{
  public: 
    carrompiece_t striker;
    carrompiece_t coin[20];
    
    gamestate_t();
    void conti();
    void update();
    void coin_coin_collision(carrompiece_t &coin1, carrompiece_t &coin2);
    void striker_coin_collision(carrompiece_t &striker, carrompiece_t &coin);
    void striker_wall_collision(carrompiece_t &striker);
    void coin_wall_collision(carrompiece_t &coin);
    void pocketing_striker_or_coin(carrompiece_t &piece,int i);
    void idle();
    void render_game();
    void loopstep();
    static void c_loopstep();
};


