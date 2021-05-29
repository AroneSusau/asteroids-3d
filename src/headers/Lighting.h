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

#include "Settings.h"
#include "Ship.h"

class Ship;

class Lighting
{
  public:
    Lighting();
    ~Lighting();

    void init();
    void world_lighting();
    void debug_lighting();
    void ship_lighting(Ship* ship);
    void fog();
};
