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

#include "Vector3.h"
#include "World.h"
#include "Materials.h"

#include <iostream>

class World;

class Wall
{
  public:

    World* world;

    float line_count = 0;
    float line_space = 0;

    float min_range = 0;
    float max_range = 0;

    float warning_range = 0;

    float red   [3] = { 1.0, 0.0, 0.0 };
    float white [3] = { 1.0, 1.0, 1.0 };

    // Order follows: front, back, left, right, top, bot
    bool warnings [6] = { false, false, false, false, false, false };

    float colours [6][3] = {
      { 1.0, 1.0, 1.0 },
      { 1.0, 1.0, 1.0 },
      { 1.0, 1.0, 1.0 },
      { 1.0, 1.0, 1.0 },
      { 1.0, 1.0, 1.0 },
      { 1.0, 1.0, 1.0 }
    };

    Wall(World* world, float line_count, float line_space, float warning_ratio);
    ~Wall();

    void wall_distance_warning(Vector3* position);
    void wall_ship_collision();
    void update_wall_color();
    void draw();
};
