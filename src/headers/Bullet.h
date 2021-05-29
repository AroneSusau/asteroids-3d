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

#include "Ship.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Settings.h"
#include "Vector3.h"
#include "V3_Math.h"
#include "Materials.h"
#include "World.h"

class World;
class Animator;

class Bullet
{
  public:

    RigidBody* body;
    Vector3* velocity;
    Animator* animator;

    World* world;

    float size;

    bool out_of_bounds;
    bool collide;

    int texture;

    Bullet();
    Bullet(World* world, Vector3* position, Vector3* velocity, int texture);
    ~Bullet();

    void draw();

    void tick();

    void update_position();
    void check_bounds();
};
