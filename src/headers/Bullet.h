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
#include "Settings.h"
#include "Vector3.h"
#include "V3_Math.h"
#include "Materials.h"
#include "World.h"

class World;

class Bullet
{
  public:

    RigidBody* body;
    Vector3* velocity;

    World* world;

    std::vector<std::vector<Vector3*>*>* frames;

    float size;

    bool out_of_bounds;
    bool collide;

    int texture;
    int current_frame;
    int start_frame;

    float frame_tick;
    float next_frame;

    Bullet();
    Bullet(World* world, Vector3* position, Vector3* velocity, int texture);
    ~Bullet();

    void draw();

    void tick();

    void update_position();
    void update_frame();
    void generate_animation_uv();
    void check_bounds();
};
