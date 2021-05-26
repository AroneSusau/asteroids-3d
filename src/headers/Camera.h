#pragma once

#include "World.h"
#include "RigidBody.h"
#include "Settings.h"

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
