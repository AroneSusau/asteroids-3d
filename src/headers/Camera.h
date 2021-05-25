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

    void place_camera();
};
