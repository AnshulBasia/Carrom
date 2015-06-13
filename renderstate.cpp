#include <GL/glut.h>
#include "renderstate.h"
#include "piece.h"
#include "gamestate.h"
#include "math.h"

extern gamestate_t g_gstate;

void renderstate_t::draw_board() 
{
  float v1x=-1.0, v1y=-1.0, v2x=1.0, v2y=-1.0, v3x=0.0, v3y=0.732;
  // draw the base
  glBegin(GL_TRIANGLES);
  glColor4f(0.25, 0.59, 0.945, 1.0);
  glVertex3f(v1x, v1y, 0.0); 
  glVertex3f(v2x, v2y, 0.0); 
  glVertex3f(v3x, v3y, 0.0); 
  glColor4f(0.945, 0.61, 0.25, 1.0);
  glVertex3f(v1x+0.05, v1y+0.05, 0.0); 
  glVertex3f(v2x-0.05, v2y+0.05, 0.0); 
  glVertex3f(v3x, v3y-0.05, 0.0); 
  glEnd();
  
  // draw the pockets
  glPushMatrix();
  glTranslatef((v1x+0.125),(v1y+0.095),0.0);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.045, 40, 16);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef((v2x-0.125),(v2y+0.095),0.0);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.045, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(v3x,(v3y-0.125),0.0);
  glColor4f(0.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.045, 40, 16);
  glPopMatrix();
  
  // Draw lines
  glPushMatrix();
  glBegin(GL_LINES);
    glRotatef(0.0, 0.0, 0.0, 0.0);
    glVertex2f (-0.65, -0.83);
    glVertex2f (0.65, -0.83);
    glVertex2f (-0.65, -0.78);
    glVertex2f (0.65, -0.78);    
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin (GL_LINES);
   glRotatef(120.0, 0.0, 0.0, 0.0);
   glVertex2f (0.68, -0.72);
   glVertex2f (0.065, 0.382);
   glVertex2f (0.63, -0.72);
   glVertex2f (0.02, 0.382);
  glEnd ();
  glPopMatrix();

  glPushMatrix();
  glBegin (GL_LINES);
   glRotatef(60.0, 0.0, 0.0, 0.0);
   glVertex2f (-0.68, -0.72);
   glVertex2f (-0.065, 0.382);
   glVertex2f (-0.63, -0.72);
   glVertex2f (-0.02, 0.382);
  glEnd ();
  glPopMatrix();
  
  // Draw end markers
  glPushMatrix();
  glTranslatef(-0.65,-0.805,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.65,-0.805,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.65,-0.72,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.043,0.382,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.043,0.382,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(-0.65,-0.72,0.0);
  glColor4f(1.0, 0.0, 0.0, 1.0);
  glutSolidSphere(0.03, 40, 16);
  glPopMatrix();

  //TODO Add the details of the board

  //Arrow or illegal region of the board

  glPushMatrix();
  glBegin(GL_LINES);
  glRotatef(30.0, 0.0, 0.0, 0.0);
  glVertex2f (-0.724, -0.805);
  glVertex2f (-0.291, -0.555);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glRotatef(150.0, 0.0, 0.0, 0.0);
  glVertex2f (0.724, -0.805);
  glVertex2f (0.291, -0.555);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glRotatef(0.0, 0.0, 0.0, 0.0);
  glVertex2f (0.0, 0.456);
  glVertex2f (0.0, -0.044);
  glEnd();
  glPopMatrix();


  glBegin(GL_LINE_LOOP);
  for(int i = 0; i < 20; i++)
  {
	  float theta = 2.0f * 3.1415926f * i / 20;	//get the current angle
	  float x = 0.1 * cos(theta);								//calculate the x component
      float y = 0.1 * sin(theta);								//calculate the y component
      glVertex2f(x-0.372, y-0.605);								//output vertex
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  for(int i = 0; i < 20; i++)
  {
	  float theta = 2.0f * 3.1415926f * i / 20;	//get the current angle
	  float x = 0.1 * cos(theta);								//calculate the x component
      float y = 0.1 * sin(theta);								//calculate the y component
      glVertex2f(x+0.372, y-0.605);								//output vertex
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  for(int i = 0; i < 20; i++)
  {
	  float theta = 2.0f * 3.1415926f * i / 20;	//get the current angle
	  float x = 0.1 * cos(theta);								//calculate the x component
      float y = 0.1 * sin(theta);								//calculate the y component
      glVertex2f(x, y+0.056);									//output vertex
  }
  glEnd();

  //Center of the board

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(1.0,1.0,0.0,1.0);
  glutSolidSphere(0.175, 6, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(1.0,0.0,1.0,1.0);
  glutSolidSphere(0.125, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(1.0,0.0,0.0,1.0);
  glutSolidSphere(0.1, 6, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(0.7,0.0,0.0,1.0);
  glutSolidSphere(0.075, 40, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(0.5,0.0,0.0,1.0);
  glutSolidSphere(0.05, 6, 16);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.42267,0.0);
  glColor4f(0.3,0.0,0.0,1.0);
  glutSolidSphere(0.025, 40, 16);
  glPopMatrix();

}

void renderstate_t::render()
{
  glLoadIdentity();
  draw_board();
  
  // draw other state_specific elements

  glLoadIdentity();
  draw_coin(p1);
  for(int i=0; i<19 ;i++)
  {
	  glLoadIdentity();
	  draw_coin(p[i]);
  }
  glFlush();
}

void renderstate_t::draw_coin(carrompiece_t& piece)
{
  if(piece.is_visible) {
    switch(piece.type) {
      case STRIKER:
        glColor4f(0.34, 0.91, 0.51, 1.0);
        glTranslatef(piece.pos.x,piece.pos.y,0.0);
        glutSolidSphere(0.038, 20, 16);
        break;
    
      case WHITE:
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glTranslatef(piece.pos.x,piece.pos.y,0.0);
        glutSolidSphere(0.03, 20, 16);
        break;
    
      case BLACK:
        glColor4f(0.37, 0.37, 0.37, 1.0);
        glTranslatef(piece.pos.x,piece.pos.y,0.0);
        glutSolidSphere(0.03, 20, 16);
        break;
        
      case RED:
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glTranslatef(piece.pos.x,piece.pos.y,0.0);
        glutSolidSphere(0.03, 20, 16);
        break;
    }
  }
}


void renderstate_t::copy_state()
{
	p1.pos.x = g_gstate.striker.pos.x;
	p1.pos.y = g_gstate.striker.pos.y;
	p1.type = g_gstate.striker.type;
	p1.is_visible = g_gstate.striker.is_visible;
  
	for(int i=0; i<19; i++)
	{
		p[i].pos.x = g_gstate.coin[i].pos.x;
		p[i].pos.y = g_gstate.coin[i].pos.y;
		p[i].type = g_gstate.coin[i].type;
		p[i].is_visible = g_gstate.coin[i].is_visible;
	}
}

