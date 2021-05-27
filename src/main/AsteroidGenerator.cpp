#include "../headers/AsteroidGenerator.h"

AsteroidGenerator::AsteroidGenerator(World* world)
{
  this->world = world;
  asteroids   = new std::vector<Asteroid*>();
}

AsteroidGenerator::~AsteroidGenerator()
{
  delete world;

  for (Asteroid* asteroids : *asteroids)
  {
    delete asteroids;
  }

  delete asteroids;
}

void AsteroidGenerator::tick() 
{
  
}

void AsteroidGenerator::draw_asteroids() 
{
  
}

