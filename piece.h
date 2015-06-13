#pragma once

typedef struct pos_t 
{
  double x;
  double y;
} pos_t;

typedef struct velocity_t 
{
  double dx;
  double dy;
} vel_t;

enum piece_type_t {STRIKER, BLACK, WHITE, RED};

class carrompiece_t 
{
  public: 
   // for gamestate
    pos_t pos;			// position of piece
    vel_t vel;			// velocity of piece
    piece_type_t type;	// type of piece
  
    // for renderstate
    bool is_visible;

    carrompiece_t();
};

