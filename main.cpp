#include <GL/glut.h>
#include "gamestate.h"
#include "renderstate.h"
#include "render_engine.h"

gamestate_t g_gstate;
renderstate_t g_rstate;

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (640,480); 
  glutInitWindowPosition (500, 300);
  glutCreateWindow ("COL100 Assignment 8");
  render_engine::init();
  glutReshapeFunc(render_engine::reshape);
  glutKeyboardFunc(render_engine::keyboard);
  glutIdleFunc(gamestate_t::c_loopstep);
  //glutFullScreen();  // Uncomment this function-call for full-screen
  glutMainLoop();
  return 0;
}

