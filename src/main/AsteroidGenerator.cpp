#include "../headers/AsteroidGenerator.h"

AsteroidGenerator::AsteroidGenerator(World* world)
{
  this->world = world;
  asteroids   = new std::vector<Asteroid*>();
  textures    = new std::vector<GLuint>();

  spawn_rate = 5;
  next_spawn = 0;
  spawn_amount = 1;
  spawn_active = true;
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
  for (size_t i = 0; i < asteroids->size(); ++i)
  {
    Asteroid* asteroid = asteroids->at(i);

    asteroid_rotate(asteroid);
    advance_asteroid(asteroid);

    if (asteroid->entered_arena)
    {
      asteroid_wall_bounce(asteroid);
    }
    else
    {
      asteroid->has_entered_arena();
    }
    
    asteroid->draw();

    asteroid_bullet_collision(asteroid);

    if (asteroid->destroyed)
    {
      delete asteroid;
      asteroids->erase(asteroids->begin() + i);
    }
  }  

  spawn();
  update_spawn();
}

void AsteroidGenerator::generate()
{
  auto tex = textures->at(V3_Math::random(1, textures->size()) - 1);
  Asteroid* asteroid = new Asteroid(tex, new Vector3(0, 0, 0));
  Vector3* position = asteroid_starting_position();

  asteroid->body->update_position(position);

  Vector3* velocity = V3_Math::normalize(V3_Math::subtract(world->ship->body->position, asteroid->body->position));
  velocity = V3_Math::multiply(velocity, 5000);

  asteroid->velocity->x = velocity->x;
  asteroid->velocity->y = velocity->y;
  asteroid->velocity->z = velocity->z;

  asteroids->push_back(asteroid);
}

void AsteroidGenerator::advance_asteroid(Asteroid* asteroid) 
{
  asteroid->body->position->x += asteroid->velocity->x * world->time->delta;
  asteroid->body->position->y += asteroid->velocity->y * world->time->delta;
  asteroid->body->position->z += asteroid->velocity->z * world->time->delta;
}

void AsteroidGenerator::asteroid_rotate(Asteroid* asteroid) 
{
  asteroid->body->orientation->x += asteroid->rotation->x * world->time->delta;
  asteroid->body->orientation->y += asteroid->rotation->y * world->time->delta;
  asteroid->body->orientation->z += asteroid->rotation->z * world->time->delta;
}

void AsteroidGenerator::asteroid_wall_bounce(Asteroid* asteroid) 
{


  if ((asteroid->body->position->x - asteroid->size < -WALL_TOTAL_DIST && asteroid->velocity->x < 0) || (asteroid->body->position->x + asteroid->size > WALL_TOTAL_DIST && asteroid->velocity->x > 0))
  {
    asteroid->velocity->x *= -1;
  }

  if ((asteroid->body->position->y - asteroid->size < -WALL_TOTAL_DIST && asteroid->velocity->y < 0) || (asteroid->body->position->y + asteroid->size > WALL_TOTAL_DIST && asteroid->velocity->y > 0))
  {
    asteroid->velocity->y *= -1;
  }

  if ((asteroid->body->position->z - asteroid->size < -WALL_TOTAL_DIST && asteroid->velocity->z < 0) || (asteroid->body->position->z + asteroid->size > WALL_TOTAL_DIST && asteroid->velocity->z > 0))
  {
    asteroid->velocity->z *= -1;
  }
}

Vector3* AsteroidGenerator::asteroid_starting_position()
{
  Vector3* position = new Vector3();

  int select = V3_Math::random(1, 4);

  int dx = V3_Math::random(1, 3) == 1 ? -1 : 1;
  int dy = V3_Math::random(1, 3) == 1 ? -1 : 1;
  int dz = V3_Math::random(1, 3) == 1 ? -1 : 1;

  int half_dist = WALL_TOTAL_DIST / 2;

  position->x = (V3_Math::random(1, half_dist)) * dx * 2;
  position->y = (V3_Math::random(1, half_dist)) * dy * 2;
  position->z = (V3_Math::random(1, half_dist)) * dz * 2;

  position->x = select == 1 ? (WALL_TOTAL_DIST + 20000) * dx : position->x;
  position->y = select == 2 ? (WALL_TOTAL_DIST + 20000) * dy : position->y;
  // position->z = select == 3 ? (WALL_TOTAL_DIST + 10000) * dz : position->z;

  position->z -= 20000;

  return position;
}

void AsteroidGenerator::asteroid_bullet_collision(Asteroid* asteroid) 
{
  std::vector<Bullet*>* bullets = world->ship->cannon->bullets;

  for (size_t i = 0; i < bullets->size(); ++i)
  {
    Bullet* bullet = bullets->at(i);

    if (asteroid->has_collided(bullet->body))
    {
      delete bullet;
      bullets->erase(bullets->begin() + i);
    }
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

void AsteroidGenerator::spawn() 
{
  if (next_spawn <= 0 && spawn_active)
  {
    for (int i = 0; i < spawn_amount; ++i)
    {
      generate();
    }

    next_spawn = spawn_rate;
    ++spawn_amount;
  }
}

void AsteroidGenerator::update_spawn() 
{
  next_spawn -= world->time->delta;
}
