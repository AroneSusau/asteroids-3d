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
#include <iostream>

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
    Vector3* rotation;

    GLuint texture;

    std::vector<std::vector<Vector3*>*>* vertices;
    std::vector<std::vector<Vector3*>*>* normals;
    std::vector<std::vector<Vector3*>*>* textcoords;

    float health;
    float max_health;
    float size;
    float bounds;
    float points;

    bool entered_arena;
    bool destroyed;

    Asteroid(GLuint texture, Vector3* v);
    ~Asteroid();

    void init();
    void init_rotation();

    void has_entered_arena();
    bool has_collided(RigidBody* o_body);
    void hit(float amount);

    void draw();
    void draw_health_bar();
};
