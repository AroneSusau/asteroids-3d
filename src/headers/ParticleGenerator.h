#pragma once

#include <vector>
#include <map>
#include <string>

#include "World.h"
#include "Particle.h"
#include "Vector3.h"
#include "Util.h"
#include "V3_Math.h"

class World;
class Particle;

class ParticleGenerator
{
  public:

    World* world;

    std::vector<Particle*>* particles;
    std::map<std::string, int>* textures;

    float tail_next_spawn;
    float tail_spawn_rate;
    float tail_spawn_amount;

    ParticleGenerator(World* world);
    ~ParticleGenerator();

    void generate_explosion(Vector3* position, float size);
    void generate_explosion_flare(Vector3* position, float size);

    void generate_ship_tail();

    void tick();

    void update_ship_tail_spawn();

    void load_textures();

    void reset();
};
