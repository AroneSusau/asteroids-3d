#pragma once

#include <vector>
#include "World.h"
#include "Vector3.h"
#include "SpriteSheet.h"

class World;
class SpriteSheet;

class Animator
{
  public:

    World* world;

    std::vector<std::vector<Vector3*>*>* frames;

    SpriteSheet* sheet;

    int current_frame;
    float frame_tick;
    float next_frame;

  Animator(World* world, SpriteSheet* sheet);
  ~Animator();

  void update_frame();
  void generate_animation_uv();
};
