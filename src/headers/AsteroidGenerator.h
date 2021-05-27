#pragma once

#include <vector>

#include "Asteroid.h"
#include "Settings.h"
#include "Util.h"
#include "World.h"

class World;

class Asteroid;

class AsteroidGenerator
{
  public:

    World* world;

    std::vector<Asteroid*>* asteroids;
    std::vector<GLuint>* textures;

    AsteroidGenerator(World* world);
    ~AsteroidGenerator();

    void tick();

    void advance_asteroid();
    void asteroid_wall_bounce();

    void load_asteroid_textures();
};
