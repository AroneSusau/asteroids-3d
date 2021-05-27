#include "../headers/AsteroidGenerator.h"

AsteroidGenerator::AsteroidGenerator(World* world)
{
  this->world = world;
  asteroids   = new std::vector<Asteroid*>();
  textures    = new std::vector<GLuint>();
}

AsteroidGenerator::~AsteroidGenerator()
{
  delete world;

  for (Asteroid* asteroids : *asteroids)
  {
    delete asteroids;
  }

  delete asteroids;
  delete textures;
}

void AsteroidGenerator::tick() 
{
  for (Asteroid* asteroid : *asteroids)
  {
    asteroid->draw();
  }  
}

void AsteroidGenerator::load_asteroid_textures()
{
  std::string t1 = ASTEROID_TEXT_1;
  std::string t2 = ASTEROID_TEXT_2;
  std::string t3 = ASTEROID_TEXT_3;
  std::string t4 = ASTEROID_TEXT_4;

  textures->push_back(Util::load_texture(t1.c_str(), false));
  textures->push_back(Util::load_texture(t2.c_str(), false));
  textures->push_back(Util::load_texture(t3.c_str(), false));
  textures->push_back(Util::load_texture(t4.c_str(), false));
}
