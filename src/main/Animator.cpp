#include "../headers/Animator.h"

Animator::Animator(World* world, SpriteSheet* sheet)
{
  this->world         = world;
  this->sheet         = sheet;
  this->current_frame = sheet->frame_start;
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
  delete sheet;
}

void Animator::generate_animation_uv() 
{
  float row_step = 1.0f / sheet->row_count;
  float col_step = 1.0f / sheet->col_count;

  for (float row = 0; row < sheet->row_count; ++row)
  {
    float row_dist = sheet->row_count - 1 - row;

    for (float col = 0; col < sheet->col_count; ++col)
    {
      frames->push_back(new std::vector<Vector3*>());

      frames->at(row * sheet->col_count + col)->push_back(new Vector3(col_step * col, row_step * row_dist, 0.0f));
      frames->at(row * sheet->col_count + col)->push_back(new Vector3(col_step * (col + 1.0f), row_step * row_dist, 0.0f));
      frames->at(row * sheet->col_count + col)->push_back(new Vector3(col_step * (col + 1.0f), row_step * (row_dist + 1.0f), 0.0f));
      frames->at(row * sheet->col_count + col)->push_back(new Vector3(col_step * col, row_step * (row_dist + 1.0f), 0.0f));
    }
  }
}

void Animator::update_frame()
{
  next_frame -= world->time->delta;

  if (next_frame <= 0)
  {
    ++current_frame;

    if (current_frame > sheet->frame_end)
    {
      current_frame = sheet->frame_start;
    }

    next_frame = frame_tick;
  }
}
