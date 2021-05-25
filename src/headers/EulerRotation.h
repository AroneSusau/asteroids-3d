#pragma once

#include "Vector3.h"
#include "V3_Math.h"
#include "RigidBody.h"

class EulerRotation
{
  public:
    Vector3 orientation = Vector3(0, 0, 0);

    EulerRotation();
    ~EulerRotation();

    static void advance(RigidBody* body, float velocity);
    static void ascend(RigidBody* body, float velocity);
    static void strafe(RigidBody* body, float velocity);

    static void yaw(RigidBody* body, float angle);
    static void pitch(RigidBody* body, float angle);
    static void roll(RigidBody* body, float angle);

    static float reset(float angle, float max);
};
