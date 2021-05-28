#include "../headers/Cannon.h"

Cannon::Cannon() 
{
}

Cannon::Cannon(Ship* ship, Vector3* position, Vector3* offset, World* world) 
{
  this->body   = new RigidBody();
  this->ship   = ship;
  this->world  = world;    
  this->offset = offset;

  this->bullets = new std::vector<Bullet*>();

  rate_of_fire    = RATE_OF_FIRE;
  next_fire       = RATE_OF_FIRE;
  bullet_velocity = BULLET_VELOCITY;

  bullet_texture  = BULLET_TEXTURE_PATH;

  active = true;

  body->update_position(position);
}

Cannon::~Cannon() 
{
  delete body;
  delete offset;

  for (Bullet* b : *bullets)
  {
    delete b;
  }

  delete bullets;
}

void Cannon::tick() 
{
  update_position();
  update_fire_rate();

  for (size_t i = 0; i < bullets->size(); ++i)
  {
    Bullet* b = bullets->at(i);

    if (b->out_of_bounds)
    {
      bullets->erase(bullets->begin() + i);
    }
    else
    {
      orient_bullets(b);
      b->tick();
      b->draw();
    }
  }
}

void Cannon::fire() 
{
  if (can_fire())
  {
    Vector3* pos = V3_Math::add(body->position, V3_Math::multiply(ship->body->forward, 15));
    Vector3* vel = V3_Math::add(V3_Math::multiply(ship->body->forward, ship->velocity->x), V3_Math::multiply(ship->body->forward, bullet_velocity));

    Bullet* b = new Bullet(world, pos, vel, bullet_texture_id);

    bullets->insert(bullets->begin(), b);
    next_fire = rate_of_fire;

    delete pos;
  }
}

bool Cannon::can_fire()
{
  return this->next_fire <= 0 && this->active;
}

void Cannon::update_position() 
{
  body->update_position(V3_Math::add(ship->body->position, offset));
}

void Cannon::update_fire_rate() 
{
if (next_fire > 0)
  {
    next_fire -= world->time->delta;
  }
}

void Cannon::orient_bullets(Bullet* bullet)
{
  bullet->body->update_forward(V3_Math::normalize(V3_Math::subtract(bullet->body->position, world->camera->body->position)));
  bullet->body->update_up(world->camera->body->up);
  bullet->body->update_right(V3_Math::cross(bullet->body->up, bullet->body->forward));
}

void Cannon::load_cannon_graphics()
{
  bullet_texture_id = Util::load_anim_texture(bullet_texture.c_str(), true);
}
