#include "../headers/ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(World* world)
{
  this->world     = world;
  this->particles = new std::vector<Particle*>();
  this->textures  = new std::vector<int>();
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

}

void ParticleGenerator::tick() 
{
  for (size_t i = 0; i < particles->size(); i++)
  {
    Particle* particle = particles->at(i);

    particle->tick();
    particle->draw();
  }
}

void ParticleGenerator::load_textures() 
{
  
}