#include "../headers/Animator.h"

Animator::Animator(World* world, float row_count, float col_count, int frame_start, int frame_end)
{
  this->world         = world;
  
  this->row_count     = row_count;
  this->col_count     = col_count;
  this->frame_start   = frame_start;
  this->frame_end     = frame_end;
  this->current_frame = frame_start;
  this->frame_tick    = 1 / FRAMES_PER_SECOND;
  this->next_frame    = frame_tick;
  this->frames        = new std::vector<std::vector<Vector3*>*>();

  generate_animation_uv();
}

Animator::~Animator()
{
  for (auto arr : *frames)
  {
    for (auto coord : *arr)
    {
      delete coord;
    }

    delete arr;
  }

  delete frames;
}

void Animator::generate_animation_uv() 
{
  float row_step = 1.0f / row_count;
  float col_step = 1.0f / col_count;

  for (float row = 0; row < row_count; ++row)
  {
    float row_dist = row_count - 1 - row;

    for (float col = 0; col < col_count; ++col)
    {
      frames->push_back(new std::vector<Vector3*>());

      frames->at(row * col_count + col)->push_back(new Vector3(col_step * col, row_step * row_dist, 0.0f));
      frames->at(row * col_count + col)->push_back(new Vector3(col_step * (col + 1.0f), row_step * row_dist, 0.0f));
      frames->at(row * col_count + col)->push_back(new Vector3(col_step * (col + 1.0f), row_step * (row_dist + 1.0f), 0.0f));
      frames->at(row * col_count + col)->push_back(new Vector3(col_step * col, row_step * (row_dist + 1.0f), 0.0f));
    }
  }
}

void Animator::update_frame()
{
  next_frame -= world->time->delta;

  if (next_frame <= 0)
  {
    ++current_frame;

    if (current_frame > frame_end)
    {
      current_frame = frame_start;
    }

    next_frame = frame_tick;
  }
}
