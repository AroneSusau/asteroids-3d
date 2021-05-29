#pragma once

#include "AsteroidGenerator.h"
#include "Axis.h"
#include "Camera.h"
#include "EulerRotation.h"
#include "Lighting.h"
#include "Mouse.h"
#include "ParticleGenerator.h"
#include "Ship.h"
#include "Settings.h"
#include "Skybox.h"
#include "Time.h"
#include "Wall.h"

class AsteroidGenerator;
class Camera;
class ParticleGenerator;
class Ship;
class Skybox;
class Mouse;
class Lighting;

class World
{
  public:

    Axis* axis;
    AsteroidGenerator* asteroid_generator;
    Camera* camera;
    Lighting* lighting;
    Mouse* mouse;
    ParticleGenerator* particle_generator;
    Ship* ship;
    Skybox* skybox;
    Time* time;
    Wall* wall;

    float viewport_width;
    float viewport_height;

    World();
    ~World();
};
