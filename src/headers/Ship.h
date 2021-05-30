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

#include "Bullet.h"
#include "Cannon.h"
#include "Materials.h"
#include "RigidBody.h"
#include "Settings.h"
#include "Util.h"
#include "World.h"

class World;
class Cannon;
class Animator;

class Ship
{
  public:

    World* world;
    RigidBody* body;
    
    Vector3* velocity;
    Vector3* acceleration;
    Vector3* rotation;

    Vector3* look;

    model_vertex model;

    Cannon* cannon;

    float roll_ratio = 0;
    float animation = 0;
    bool firing = false;

    std::string model_filename;
    std::string material_path;
    std::string texture_path;
    int ship_id;

    Ship(World* world);
    ~Ship();

    void update_position();
    void update_velocity();
    void update_look();
    void update_animation();

    void ship_forward_rotation();
    void mouse_ship_rotation();

    void decelerate();
    bool can_accelerate(move_state_t state, move_state_t expected, float velocity, float clamp);

    void tick();

    void shoot();

    void draw();
    void draw_ship();
    void draw_wings();

    void load_ship_graphics();

    void on_key_press(unsigned char key, int x, int y);
    void on_key_release(unsigned char key, int x, int y);
};
