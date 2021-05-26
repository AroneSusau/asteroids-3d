#pragma once

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <iostream>

#include "Vector3.h"
#include "Settings.h"

class Mouse
{
  public:
    
    Vector3* position;
    Vector3* ratio;
    
    Mouse();
    ~Mouse();

    void on_mouse_move(int x, int y);
    void update_move_vector();
};
