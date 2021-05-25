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

class Time
{
  public:

    float time  = 0;
    float now   = 0;
    float delta = 0;

    Time();
    ~Time();

    void tick();
    void update();
};
