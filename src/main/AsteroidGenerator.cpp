#include "../headers/AsteroidGenerator.h"

AsteroidGenerator::AsteroidGenerator(World* world)
{
  this->world   = world;
  asteroids     = new std::vector<Asteroid*>();
  textures      = new std::vector<GLuint>();

  spawn_rate    = ASTEROID_SPAWN_RATE;
  next_spawn    = ASTEROID_SPAWN_NEXT;
  spawn_amount  = ASTEROID_SPAWN_AMOUNT;
  max_asteroids = ASTEROID_SPAWN_MAX;
  spawn_active  = ASTEROID_ACTIVE;
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
    orient_health_bar(asteroid);
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
    asteroid_asteroid_collision(asteroid, i);
    asteroid_ship_collision(asteroid);

    if (asteroid->destroyed)
    {
      delete asteroid;
      asteroids->erase(asteroids->begin() + i);
    }
  }  
}

void AsteroidGenerator::generate()
{
  auto tex = textures->at(V3_Math::random(1, textures->size()) - 1);
  Asteroid* asteroid = new Asteroid(world, tex, new Vector3(0, 0, 0));

  Vector3* position = asteroid_starting_position();

  asteroid->body->update_position(position);

  Vector3* velocity = V3_Math::normalize(V3_Math::subtract(world->ship->body->position, asteroid->body->position));
  velocity = V3_Math::multiply(velocity, V3_Math::random(ASTEROID_MIN_VELOCITY, ASTEROID_MAX_VELOCITY));

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

  int select = V3_Math::random(1, 3);

  int dx = V3_Math::random(1, 2) == 1 ? -1 : 1;
  int dy = V3_Math::random(1, 2) == 1 ? -1 : 1;
  int dz = V3_Math::random(1, 2) == 1 ? -1 : 1;

  position->x = (V3_Math::random(1, WALL_TOTAL_DIST)) * dx * 2;
  position->y = (V3_Math::random(1, WALL_TOTAL_DIST)) * dy * 2;
  position->z = (V3_Math::random(1, WALL_TOTAL_DIST)) * dz * 2;

  position->x = select == 1 ? (WALL_TOTAL_DIST * 4) * dx : position->x;
  position->y = select == 2 ? (WALL_TOTAL_DIST * 4) * dy : position->y;
  position->z = select == 3 ? (WALL_TOTAL_DIST * 4) * dz : position->z;

  return position;
}

void AsteroidGenerator::asteroid_ship_collision(Asteroid* asteroid)
{
  if (world->ship->active && asteroid->has_collided(world->ship->body))
  {
    world->game_state = GAME_OVER;
    world->player_death_time = world->time->now;
    asteroid->destroyed = true;
    world->ship->active = false;
    world->particle_generator->generate_ship_explosion(V3_Math::add(world->ship->body->position, V3_Math::multiply(world->ship->body->forward, 10)), 5);
  }
}

void AsteroidGenerator::asteroid_bullet_collision(Asteroid* asteroid) 
{
  std::vector<Bullet*>* bullets = world->ship->cannon->bullets;

  for (size_t i = 0; i < bullets->size(); ++i)
  {
    Bullet* bullet = bullets->at(i);

    if (asteroid->has_collided(bullet->body))
    {
      asteroid->hit(BULLET_DAMAGE);

      if (asteroid->destroyed)
      {
        world->player_points += asteroid->points;
        world->particle_generator->generate_explosion(asteroid->body->position, asteroid->size / 30);
      }

      delete bullet;
      bullets->erase(bullets->begin() + i);
    }
  }
}

void AsteroidGenerator::asteroid_asteroid_collision(Asteroid* a, int index)
{
  if (a->entered_arena)
  {
    for (size_t j = index + 1; j < asteroids->size(); ++j) {
      Asteroid* b = asteroids->at(j);

      if (b->entered_arena && has_collided(a, b))
      {
        float a_x = a->velocity->x;
        float a_y = a->velocity->y; 
        float a_z = a->velocity->z;
        float b_x = b->velocity->x;
        float b_y = b->velocity->y;
        float b_z = b->velocity->z;

        a->velocity->x = b_x;
        a->velocity->y = b_y;
        a->velocity->z = b_z;

        b->velocity->x = a_x;
        b->velocity->y = a_y;
        b->velocity->z = a_z;

        a->body->update_position(V3_Math::add(a->body->position, V3_Math::multiply(V3_Math::multiply(a->velocity, world->time->delta), 2)));
        b->body->update_position(V3_Math::add(b->body->position, V3_Math::multiply(V3_Math::multiply(b->velocity, world->time->delta), 2)));
      }
    }
  }
}

bool AsteroidGenerator::has_collided(Asteroid* a, Asteroid* b)
{
  return V3_Math::magnitude(V3_Math::subtract(b->body->position, a->body->position)) < (a->size + b->size);
}

void AsteroidGenerator::orient_health_bar(Asteroid* asteroid)
{
  asteroid->body->update_forward(V3_Math::normalize(V3_Math::subtract(asteroid->body->position, world->ship->body->position)));
  asteroid->body->update_up(world->ship->body->up);
  asteroid->body->update_right(V3_Math::cross(asteroid->body->up, asteroid->body->forward));
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
  if (spawn_active && next_spawn <= 0)
  {
    for (int i = 0; i < spawn_amount; ++i)
    {
      if (asteroids->size() <= max_asteroids)
      {
        generate();
      }
    }

    next_spawn = spawn_rate;
    spawn_amount += spawn_amount <= max_asteroids ? 1 : 0;
  }
}

void AsteroidGenerator::update_spawn() 
{
  next_spawn -= world->time->delta;
}

void AsteroidGenerator::debug_asteroid()
{
  if (ASTEROID_DEBUG)
  {
    generate();
    asteroids->at(0)->body->update_position(new Vector3(0, 0, -5000));
    asteroids->at(0)->velocity = new Vector3(0, 0, 0);
  }
}

void AsteroidGenerator::reset()
{
  spawn_rate    = ASTEROID_SPAWN_RATE;
  next_spawn    = ASTEROID_SPAWN_NEXT;
  spawn_amount  = ASTEROID_SPAWN_AMOUNT;
  max_asteroids = ASTEROID_SPAWN_MAX;
  spawn_active  = ASTEROID_ACTIVE;

  for (Asteroid* asteroids : *asteroids)
  {
    delete asteroids;
  }

  asteroids->clear();
}