#pragma once

#include "World.h"
#include "RigidBody.h"

class World;

class Camera
{
  public:
    
    World* world;
    RigidBody* body;
    
    Camera();
    ~Camera();

    void update_look();
    void place_camera();

    void update_position();
    void on_key_press(unsigned char key, int x, int y);
    void on_key_release(unsigned char key, int x, int y);
};
