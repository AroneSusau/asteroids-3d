#include "../headers/Bullet.h"

Bullet::Bullet()
{
  body     = new RigidBody();
  velocity = new Vector3();
  
  size = BULLET_SIZE;

  out_of_bounds = false;
  collide       = false;
}

Bullet::Bullet(World* world, Vector3* position, Vector3* velocity, int texture)
{
  this->body     = new RigidBody();
  this->velocity = velocity;
  this->world    = world;

  size = BULLET_SIZE;

  out_of_bounds = false;

  body->update_position(position);
}

Bullet::~Bullet()
{
  delete body;
  delete velocity;
}

void Bullet::draw() 
{
  glPushMatrix();
  glTranslatef(body->position->x, body->position->y, body->position->z);
  glColor3f(1, 1, 1);
  glScalef(1, 1, 1);
  glutSolidCube(BULLET_SIZE);
  glPopMatrix();
}

void Bullet::tick() 
{
  update_position();
  check_bounds();
}

void Bullet::update_position() 
{
  body->position->x += velocity->x * world->time->delta;
  body->position->y += velocity->y * world->time->delta;
  body->position->z += velocity->z * world->time->delta;
}

void Bullet::check_bounds()
{
  out_of_bounds = (
    body->position->x <= -WALL_TOTAL_DIST || body->position->x >= WALL_TOTAL_DIST ||
    body->position->y <= -WALL_TOTAL_DIST || body->position->y >= WALL_TOTAL_DIST ||
    body->position->z <= -WALL_TOTAL_DIST || body->position->z >= WALL_TOTAL_DIST
  );
}
