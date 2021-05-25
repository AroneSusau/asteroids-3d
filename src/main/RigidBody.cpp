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
  delete position;
  position = other;
}

void RigidBody::update_forward(Vector3* other)
{
  delete forward;
  forward = std::move(other);
}

void RigidBody::update_up(Vector3* other)
{
  delete up;
  up = std::move(other);
}

void RigidBody::update_right(Vector3* other)
{
  delete right;
  right = std::move(other);
}

void RigidBody::update_look(Vector3* other)
{
  delete look;
  look = std::move(other);
}