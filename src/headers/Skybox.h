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

#include <string>

#include "Util.h"
#include "World.h"

class World;

class Skybox
{
  public:

    GLuint textures [6] = {0, 0, 0, 0, 0, 0};
    std::string filenames [6] = {"", "", "", "", "", ""};

    Skybox();
    ~Skybox();

    World* world;

    void load_skybox_textures();
    void draw();
};


