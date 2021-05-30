#include "../headers/ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(World* world)
{
  this->world     = world;
  this->particles = new std::vector<Particle*>();
  this->textures  = new std::map<std::string, int>();

  tail_spawn_rate = 0.05;
  tail_next_spawn = tail_spawn_rate;
  tail_spawn_amount = 100;
}

ParticleGenerator::~ParticleGenerator()
{
  for (Particle* p : *particles)
  {
    delete p;
  }

  delete particles;
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

  particles->push_back(p1);
  particles->push_back(p2);
  particles->push_back(p3);
}

void ParticleGenerator::tick() 
{
  // update_ship_tail_spawn();

  for (size_t i = 0; i < particles->size(); i++)
  {
    Particle* particle = particles->at(i);

    if (particle->finished)
    {
      delete particle;
      particles->erase(particles->begin() + i);
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

    particles->push_back(p);
  }
}

void ParticleGenerator::generate_ship_tail()
{
  for (int i = 0; i < tail_spawn_amount; ++i)
  {
    Particle* p = new Particle(
      world, 
      PARTICLE_SHIP_TAIL_SHEET, 
      textures->at(PARTICLE_SHIP_TAIL), 
      0.8, 
      PARTICLE_TIME, 
      0.5,
      true);
  
    float sidex = V3_Math::random(1, 2) == 1 ? 1.10 : -1.10;
    float amountx = V3_Math::random(50, 70) / 100.0f;

    float sidey = V3_Math::random(1, 2) == 1 ? 1 : -1;
    float amounty = V3_Math::random(10, 25) / 100.0f;

    float vel_ratio = V3_Math::random(100, 300) / 100.0f;

    p->body->update_position(V3_Math::subtract(
      world->ship->body->position, 
      V3_Math::add(V3_Math::multiply(world->ship->body->forward, 1.5), 
      V3_Math::add(V3_Math::multiply(world->ship->body->right, sidex * amountx), 
      V3_Math::multiply(world->ship->body->up, sidey * amounty)))
    ));
    
    p->velocity = V3_Math::add(world->ship->velocity, V3_Math::multiply(world->ship->body->forward, -vel_ratio));

    particles->push_back(p);
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

void ParticleGenerator::update_ship_tail_spawn() 
{
  tail_next_spawn -= world->time->delta;

  if (tail_next_spawn <= 0)
  {
    generate_ship_tail();
    tail_next_spawn = tail_spawn_rate;
  }  
}

void ParticleGenerator::reset()
{
  for (Particle* p : *particles)
  {
    delete p;
  }

  particles->clear();
}