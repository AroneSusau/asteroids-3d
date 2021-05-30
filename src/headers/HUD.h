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

#include "World.h"

class World;

class HUD
{
  public:

    World* world;

    HUD(World* world);
    ~HUD();

    void  tick();

    void start_screen();
    void game_over_screen();
    void playing_screen();
};
