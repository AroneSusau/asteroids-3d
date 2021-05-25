#include "../headers/RigidBody.h"
#include <memory>

RigidBody::RigidBody()
{  
  position = new Vector3(0, 0, 100);
  forward  = new Vector3(0, 0, -100);
  up       = new Vector3(0, 1, 0);
  right    = new Vector3(-1, 0, 0);
  look     = new Vector3(0, 0, -100);

  orientation = new Vector3(0, 0, 0);
}

RigidBody::~RigidBody() {
  delete position;
  delete forward;
  delete up;
  delete right;
  delete look;
  delete orientation;
}

void RigidBody::update_position(Vector3* other)
{
  position->x = other->x;
  position->y = other->y;
  position->z = other->z;
}

void RigidBody::update_forward(Vector3* other)
{
  forward->x = other->x;
  forward->y = other->y;
  forward->z = other->z;
}

void RigidBody::update_up(Vector3* other)
{
  up->x = other->x;
  up->y = other->y;
  up->z = other->z;
}

void RigidBody::update_right(Vector3* other)
{
  right->x = other->x;
  right->y = other->y;
  right->z = other->z;
}

void RigidBody::update_look(Vector3* other)
{
  look->x = other->x;
  look->y = other->y;
  look->z = other->z;
}