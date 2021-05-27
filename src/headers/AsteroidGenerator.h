#pragma once

#include <vector>

#include "../headers/Asteroid.h"
#include "../headers/World.h"

class World;

class AsteroidGenerator
{
  public:

    World* world;

    std::vector<Asteroid*>* asteroids;

    AsteroidGenerator(World* world);
    ~AsteroidGenerator();

    void tick();
    void draw_asteroids();
};
