#pragma once

#include "Vector3.h"

typedef enum { 
  INCREASE = 1, 
  DECREASE = 2, 
  NEUTRAL  = 3 
} move_state_t;

class RigidBody
{
  public:

    Vector3* position = new Vector3(0, 0, 0);
    Vector3* forward  = new Vector3(0, 0, 0);
    Vector3* up       = new Vector3(0, 0, 0);
    Vector3* right    = new Vector3(0, 0, 0);
    Vector3* look     = new Vector3(0, 0, 0);

    Vector3* orientation = new Vector3(0, 0, 0);

    move_state_t advance = NEUTRAL;
    move_state_t strafe  = NEUTRAL;
    move_state_t ascend  = NEUTRAL;

    move_state_t yaw   = NEUTRAL;
    move_state_t pitch = NEUTRAL;
    move_state_t roll  = NEUTRAL;

    RigidBody();
    ~RigidBody();

    void update_position(Vector3* other);
    void update_forward(Vector3* other);
    void update_up(Vector3* other);
    void update_right(Vector3* other);
    void update_look(Vector3* other);
    void update_orientation(Vector3* other);
};
