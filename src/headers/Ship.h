#pragma once

#include "World.h"
#include "RigidBody.h"

class World;

class Ship
{
  public:

    World* world;
    RigidBody* body;

    Ship();
    ~Ship();
};
