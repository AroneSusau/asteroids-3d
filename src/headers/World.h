#pragma once

#include "Settings.h"

#include "Camera.h"
#include "EulerRotation.h"
#include "Axis.h"
#include "Time.h"
#include "Ship.h"
#include "Wall.h"

class Camera;
class Ship;

class World
{
  public:

    Axis* axis;
    Camera* camera;
    Ship* ship;
    Time* time;
    Wall* wall;

    World();
    ~World();
};
