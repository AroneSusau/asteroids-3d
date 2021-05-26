#pragma once

#include <string>

class Vector3
{

  public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    Vector3(Vector3 && o) :
      x(o.x),
      y(o.y),
      z(o.z) {}

    std::string to_string()
    {
      return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
    }

    ~Vector3() {}
};
