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

    float spawn_rate;
    float next_spawn;
    int spawn_amount;
    int max_asteroids;

    bool spawn_active;

    std::vector<Asteroid*>* asteroids;
    std::vector<GLuint>* textures;

    AsteroidGenerator(World* world);
    ~AsteroidGenerator();

    void tick();

    void generate();

    void advance_asteroid(Asteroid* asteroid);
    void asteroid_rotate(Asteroid* asteroid);
    void asteroid_wall_bounce(Asteroid* asteroid);
    void asteroid_bullet_collision(Asteroid* asteroid);
    void orient_health_bar(Asteroid* asteroid);

    void spawn();
    void update_spawn();
    
    Vector3* asteroid_starting_position();

    void load_asteroid_textures();
};
