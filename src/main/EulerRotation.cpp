#include "../headers/EulerRotation.h"

EulerRotation::EulerRotation() {}
EulerRotation::~EulerRotation() {}

void EulerRotation::EulerRotation::advance(RigidBody* body, float velocity) 
{
  body->update_position(
    V3_Math::add(
      body->position, 
      V3_Math::multiply(body->forward, velocity)
    ));
}

void EulerRotation::ascend(RigidBody* body, float velocity) 
{
  body->update_position(
    V3_Math::add(
      body->position, 
      V3_Math::multiply(body->up, velocity)
    ));
}

void EulerRotation::strafe(RigidBody* body, float velocity) 
{
  body->update_position(
    V3_Math::add(
      body->position, 
      V3_Math::multiply(body->right, velocity)
    ));
}

void EulerRotation::yaw(RigidBody* body, float angle)
{
  float rads = V3_Math::deg_to_rad(angle);

  body->update_forward(V3_Math::normalize(
    V3_Math::subtract(
      V3_Math::multiply(body->forward, cosf(rads)),
      V3_Math::multiply(body->right, sinf(rads)))
  ));

  body->update_right(V3_Math::cross(body->forward, body->up));
}

void EulerRotation::pitch(RigidBody* body, float angle)
{  
  float rads = V3_Math::deg_to_rad(angle);

  body->update_forward(V3_Math::normalize(
    V3_Math::add(
      V3_Math::multiply(body->forward, cosf(rads)),
      V3_Math::multiply(body->up, sinf(rads)))
  ));

  body->update_up(V3_Math::cross(body->forward, body->right));
  body->update_up(V3_Math::multiply(body->up, -1));
}

void EulerRotation::roll(RigidBody* body, float angle)
{
  float rads = V3_Math::deg_to_rad(angle);

  body->update_right(V3_Math::normalize(
    V3_Math::add(
      V3_Math::multiply(body->right, cosf(rads)),
      V3_Math::multiply(body->up, sinf(rads)))
  ));

  body->update_up(V3_Math::cross(body->forward, body->right));
  body->update_up(V3_Math::multiply(body->up, -1));
}

void EulerRotation::rotate(RigidBody* body, float angle)
{
  std::cout << "ORI: " << body->orientation->to_string() << std::endl;
  std::cout << "FOR: " << body->forward->to_string() << std::endl;
  body->update_orientation(V3_Math::subtract(body->orientation, V3_Math::multiply(body->forward, angle)));

  body->orientation->x = EulerRotation::reset(body->orientation->x, 360.0f);
  body->orientation->y = EulerRotation::reset(body->orientation->y, 360.0f);
  body->orientation->z = EulerRotation::reset(body->orientation->z, 360.0f);
}

float EulerRotation::reset(float angle, float max)
{
  if (angle >= max)
  {
    angle = max - angle;
  }
  else if (angle < 0.0f)
  {
    angle = angle + max;
  }

  return angle;
}