#include "../headers/SpriteSheet.h"

SpriteSheet::SpriteSheet(float row_count, float col_count, float frame_start, float frame_end) {
  this->row_count     = row_count;
  this->col_count     = col_count;
  this->frame_start   = frame_start;
  this->frame_end     = frame_end;
}

SpriteSheet::~SpriteSheet()
{}