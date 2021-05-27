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

#include <vector>

#include "Materials.h"
#include "RigidBody.h"
#include "Settings.h"
#include "Util.h"
#include "World.h"

#define SPHERE_DIVISIONS 50

class World;

class Asteroid
{
  public:

    RigidBody* body;
    Vector3* velocity;

    std::vector<std::vector<Vector3*>*>* vertices;
    std::vector<std::vector<Vector3*>*>* normals;
    std::vector<std::vector<Vector3*>*>* textcoords;

    Asteroid();
    ~Asteroid();

    void init();

    void draw();
};
