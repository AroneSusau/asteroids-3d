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
  gluLookAt(
    body->position->x, body->position->y, body->position->z,
    body->look->x,     body->look->y,     body->look->z,
    body->up->x,       body->up->y,       body->up->z);
}

void Camera::update_look()
{
  body->update_look(V3_Math::add(body->position, body->forward));
}

void Camera::update_position()
{
  float move_speed = 16;
  float rotation_speed = 45;

  if (body->advance == INCREASE)
  {
    EulerRotation::advance(body, move_speed * world->time->delta);
  }
  
  if (body->advance == DECREASE)
  {
    EulerRotation::advance(body, -move_speed * world->time->delta);
  }
  
  if (body->strafe == INCREASE)
  {
    EulerRotation::strafe(body, move_speed * world->time->delta);
  }
  
  if (body->strafe == DECREASE)
  {
    EulerRotation::strafe(body, -move_speed * world->time->delta);
  }

  if (body->pitch == INCREASE)
  {
    EulerRotation::pitch(body, rotation_speed * world->time->delta);
  }

  if (body->pitch == DECREASE)
  {
    EulerRotation::pitch(body, -rotation_speed * world->time->delta);
  }

  if (body->yaw == INCREASE)
  {
    EulerRotation::yaw(body, rotation_speed * world->time->delta);
  }

  if (body->yaw == DECREASE)
  {
    EulerRotation::yaw(body, rotation_speed * world->time->delta);
  }

  if (body->roll == INCREASE)
  {
    EulerRotation::roll(body, -rotation_speed * world->time->delta);
  }

  if (body->roll == DECREASE)
  {
    EulerRotation::roll(body, rotation_speed * world->time->delta);
  }
}

void Camera::on_key_press(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'A':
  case 'a':
    body->strafe = DECREASE;
    break;
  case 'D':
  case 'd':
    body->strafe = INCREASE;
    break;
  case 'W':
  case 'w':
    body->advance = INCREASE;
    break;
  case 'S':
  case 's':
    body->advance = DECREASE;
    break;
  case 'i':
  case 'I':
    body->pitch = INCREASE;
    break;
  case 'k':
  case 'K':
    body->pitch = DECREASE;
    break;
  case 'j':
  case 'J':
    body->yaw = DECREASE;
    break;
  case 'l':
  case 'L':
    body->yaw = INCREASE;
    break;
  case 'q':
  case 'Q':
    body->roll = DECREASE;
    break;
  case 'e':
  case 'E':
    body->roll = INCREASE;
    break;
  default:
    break;
  }
}

void Camera::on_key_release(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'A':
    case 'a':
      body->strafe = NEUTRAL;
      break;
    case 'D':
    case 'd':
      body->strafe = NEUTRAL;
      break;
    case 'W':
    case 'w':
      body->advance = NEUTRAL;
      break;
    case 'S':
    case 's':
      body->advance = NEUTRAL;
      break;
    case 'i':
    case 'I':
      body->pitch = NEUTRAL;
      break;
    case 'k':
    case 'K':
      body->pitch = NEUTRAL;
      break;
    case 'j':
    case 'J':
      body->yaw = NEUTRAL;
      break;
    case 'l':
    case 'L':
      body->yaw = NEUTRAL;
      break;
    case 'q':
    case 'Q':
      body->roll = NEUTRAL;
      break;
    case 'e':
    case 'E':
      body->roll = NEUTRAL;
      break;
  }
}