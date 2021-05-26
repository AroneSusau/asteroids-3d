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

#include "Wall.h"
#include "Vector3.h"

#include <iostream>

class Wall
{
  public:

    float line_count = 0;
    float line_space = 0;

    float min_range = 0;
    float max_range = 0;

    float warning_range = 0;

    float red   [3] = { 0.8, 0.0, 0.0 };
    float white [3] = { 0.4, 0.4, 0.4 };

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

    Wall(float line_count, float line_space, float warning_ratio);
    ~Wall();

    void wall_distance_warning(Vector3* position);
    void update_wall_color();
    void draw();
};
