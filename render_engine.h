#ifndef RENDERER_H_
#define RENDERER_H_

class render_engine 
{
  public:
    static void init();
    static void reshape(int w, int h);
    static void keyboard(unsigned char key, int x, int y);
};

#endif

