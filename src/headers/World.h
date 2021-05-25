#pragma once

#include "Axis.h"
#include "Camera.h"
#include "EulerRotation.h"
#include "Ship.h"
#include "Settings.h"
#include "Skybox.h"
#include "Time.h"
#include "Wall.h"

class Camera;
class Ship;
class Skybox;

class World
{
  public:

    Axis* axis;
    Camera* camera;
    Ship* ship;
    Skybox* skybox;
    Time* time;
    Wall* wall;

    World();
    ~World();
};
