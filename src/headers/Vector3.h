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

    std::string to_string()
    {
      return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
    }

    ~Vector3() {}
};
