#include "../headers/ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(World* world)
{
  this->world     = world;
  this->textures  = new std::map<std::string, int>();

  this->asteroid_particles = new std::vector<Particle*>();

  tail_spawn_rate   = 0.05;
  tail_next_spawn   = tail_spawn_rate;
  tail_spawn_amount = 10;
}

ParticleGenerator::~ParticleGenerator()
{
  for (Particle* p : *asteroid_particles)
  {
    delete p;
  }

  delete asteroid_particles;
  delete textures;
}

void ParticleGenerator::generate_explosion(Vector3* position, float size) 
{
  Particle* p1 = new Particle(world, PARTICLE_EXPLOSION_1_SHEET, textures->at(PARTICLE_EXPLOSION_1), size, PARTICLE_FRAME);
  Particle* p2 = new Particle(world, PARTICLE_EXPLOSION_2_SHEET, textures->at(PARTICLE_EXPLOSION_2), size, PARTICLE_FRAME);
  Particle* p3 = new Particle(world, PARTICLE_EXPLOSION_3_SHEET, textures->at(PARTICLE_EXPLOSION_3), size, PARTICLE_FRAME);

  p1->body->update_position(position);
  p2->body->update_position(V3_Math::add(position, world->camera->body->forward));
  p3->body->update_position(V3_Math::add(position, V3_Math::multiply(world->camera->body->forward, 2)));

  generate_explosion_flare(position, size);

  asteroid_particles->push_back(p1);
  asteroid_particles->push_back(p2);
  asteroid_particles->push_back(p3);
}

void ParticleGenerator::tick() 
{
  tick_asteroid_particles();
}

void ParticleGenerator::tick_asteroid_particles() 
{
  for (size_t i = 0; i < asteroid_particles->size(); i++)
  {
    Particle* particle = asteroid_particles->at(i);

    if (particle->finished)
    {
      delete particle;
      asteroid_particles->erase(asteroid_particles->begin() + i);
    }
    else
    {
      particle->tick();
      particle->draw();
    }
  }
}

void ParticleGenerator::generate_explosion_flare(Vector3* position, float size)
{
  for (int i = 0; i < PARTICLE_FLARE_COUNT; ++i)
  {
    float countdown = (float) V3_Math::random(50, 150) / 100;
    float size_n    = (float) V3_Math::random(2, PARTICLE_FLARE_SIZE_FACTOR);

    Particle* p = new Particle(
      world, 
      PARTICLE_EXPLOSION_4_SHEET, 
      textures->at(PARTICLE_EXPLOSION_4), 
      size_n, 
      PARTICLE_TIME, 
      countdown);
  
    float dx = V3_Math::random(1, 2) == 1 ? 1 : -1;
    float dy = V3_Math::random(1, 2) == 1 ? 1 : -1;
    float dz = V3_Math::random(1, 2) == 1 ? 1 : -1;

    p->body->update_position(position);
    
    p->velocity->x = dx * V3_Math::random(PARTICLE_FLARE_MIN_VELOCITY, PARTICLE_FLARE_MAX_VELOCITY);
    p->velocity->y = dy * V3_Math::random(PARTICLE_FLARE_MIN_VELOCITY, PARTICLE_FLARE_MAX_VELOCITY);
    p->velocity->z = dz * V3_Math::random(PARTICLE_FLARE_MIN_VELOCITY, PARTICLE_FLARE_MAX_VELOCITY);

    asteroid_particles->push_back(p);
  }
}

void ParticleGenerator::load_textures() 
{
  textures->insert(std::pair<std::string, int>(PARTICLE_EXPLOSION_1, Util::load_anim_texture(PARTICLE_EXPLOSION_1, true)));
  textures->insert(std::pair<std::string, int>(PARTICLE_EXPLOSION_2, Util::load_anim_texture(PARTICLE_EXPLOSION_2, true)));
  textures->insert(std::pair<std::string, int>(PARTICLE_EXPLOSION_3, Util::load_anim_texture(PARTICLE_EXPLOSION_3, true)));
  textures->insert(std::pair<std::string, int>(PARTICLE_EXPLOSION_4, Util::load_anim_texture(PARTICLE_EXPLOSION_4, true)));

  textures->insert(std::pair<std::string, int>(PARTICLE_SHIP_TAIL, Util::load_anim_texture(PARTICLE_SHIP_TAIL, true)));
}

void ParticleGenerator::reset()
{
  for (Particle* p : *asteroid_particles)
  {
    delete p;
  }

  asteroid_particles->clear();
}