#pragma once

#include <vector>

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
    std::vector<int>* textures;

    ParticleGenerator(World* world);
    ~ParticleGenerator();

    void generate_explosion(Vector3* position, float size);

    void tick();

    void load_textures();
};
