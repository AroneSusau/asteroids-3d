#pragma once

#include <vector>
#include "World.h"
#include "Vector3.h"

class World;

class Animator
{
  public:

    World* world;

    std::vector<std::vector<Vector3*>*>* frames;

    int current_frame;
    int frame_start;
    int frame_end;

    float row_count;
    float col_count;

    float frame_tick;
    float next_frame;

  Animator(World* world, float row_count, float col_count, int frame_start, int frame_end);
  ~Animator();

  void update_frame();
  void generate_animation_uv();
};
