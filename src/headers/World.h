#pragma once

#include "AsteroidGenerator.h"
#include "Axis.h"
#include "Camera.h"
#include "EulerRotation.h"
#include "HUD.h"
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
class HUD;
class ParticleGenerator;
class Ship;
class Skybox;
class Mouse;
class Lighting;

typedef enum { GAME_START, GAME_PLAYING, GAME_OVER } gamestate_t;

class World
{
  public:

    Axis* axis;
    AsteroidGenerator* asteroid_generator;
    Camera* camera;
    HUD* hud;
    Lighting* lighting;
    Mouse* mouse;
    ParticleGenerator* particle_generator;
    Ship* ship;
    Skybox* skybox;
    Time* time;
    Wall* wall;

    float viewport_width;
    float viewport_height;

    float player_points;
    float player_death_time;

    gamestate_t game_state;

    World();
    ~World();
};
