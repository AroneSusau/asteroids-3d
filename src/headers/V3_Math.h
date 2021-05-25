#pragma once

#include <math.h>

#include "Vector3.h"

class V3_Math
{
  public:
    V3_Math() {}
    ~V3_Math() {}

    static Vector3* add(Vector3* a, Vector3* b)
    {
      return new Vector3(
        a->x + b->x, 
        a->y + b->y, 
        a->z + b->z
      );
    }

    static Vector3* subtract(Vector3* a, Vector3* b)
    {
      return new Vector3(
        a->x - b->x, 
        a->y - b->y, 
        a->z - b->z
      );
    }

    static Vector3* multiply(Vector3* a, Vector3* b)
    {
      return new Vector3(
        a->x * b->x, 
        a->y * b->y, 
        a->z * b->z
      );
    }

    static Vector3* multiply(Vector3* a, float factor)
    {
      return new Vector3(
        a->x * factor, 
        a->y * factor, 
        a->z * factor
      );
    }

    static Vector3* normalize(Vector3* a)
    {
      float mag = V3_Math::magnitude(a);

      return mag > 0 ? new Vector3(
        a->x / mag, 
        a->y / mag, 
        a->z / mag
      ) : new Vector3( 0, 0, 0);
    }

    static float magnitude(Vector3* a)
    {
      return sqrtf(
        powf(a->x, 2) + 
        powf(a->y, 2) + 
        powf(a->z, 2)
      );
    }

    static float dot(Vector3* a, Vector3* b)
    {
      return a->x * b->x + a->y * b->y + a->z * b->z;
    }

    static Vector3* cross(Vector3* a, Vector3* b)
    { 
      return new Vector3(
        a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x
      );
    }

    static float deg_to_rad(float theta)
    {
      return theta * M_PI / 180.0f;
    }
};
