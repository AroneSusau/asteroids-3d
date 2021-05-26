#include "../headers/Camera.h"

Camera::Camera() 
{
  body = new RigidBody();
}

Camera::~Camera()
{
  delete body;
}

void Camera::place_camera()
{ 
  body->update_forward(world->ship->body->forward);
  body->update_look(world->ship->body->look);
  body->update_up(world->ship->body->up);
  body->update_right(world->ship->body->right);

  body->update_position(
    V3_Math::subtract(
      V3_Math::subtract(world->ship->body->position, V3_Math::multiply(world->ship->body->forward, CAMERA_BACK_DIST)), 
      V3_Math::multiply(world->ship->body->up, -CAMREA_UP_DIST)
  ));

  gluLookAt(
    body->position->x, body->position->y, body->position->z,
    body->look->x,     body->look->y,     body->look->z,
    body->up->x,       body->up->y,       body->up->z);
}
