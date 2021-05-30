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
  if (world->game_state == GAME_PLAYING || world->game_state == GAME_OVER)
  {
    body->update_forward(world->ship->body->forward);
    body->update_look(world->ship->body->look);
    body->update_up(world->ship->body->up);
    body->update_right(world->ship->body->right);

    float backward_delay = CAMERA_BACK_DIST + CAMERA_BACK_DELAY * world->ship->animation;
    float up_delay = CAMREA_UP_DIST + -CAMREA_UP_DIST * world->ship->animation;

    Vector3* back = V3_Math::subtract(world->ship->body->position, V3_Math::multiply(world->ship->body->forward, backward_delay));
    Vector3* up   = V3_Math::add(back, V3_Math::multiply(world->ship->body->up, up_delay));

    body->update_position(up);

    gluLookAt(
      body->position->x, body->position->y, body->position->z,
      body->look->x,     body->look->y,     body->look->z,
      body->up->x,       body->up->y,       body->up->z);
  }
  else if (world->game_state == GAME_START)
  {
    world->start_screen();
  }
}
