#pragma once

#include "World.h"
#include "RigidBody.h"
#include "Settings.h"

class World;

class Ship
{
  public:

    World* world;
    RigidBody* body;

    Ship();
    ~Ship();

    void update_position();
    
    void draw();

    void on_key_press(unsigned char key, int x, int y);
    void on_key_release(unsigned char key, int x, int y);
};
