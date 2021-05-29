#pragma once

class SpriteSheet
{
  public:

    float row_count;
    float col_count;
    float frame_start;
    float frame_end;

    SpriteSheet(float row_count, float col_count, float frame_start, float frame_end);
    ~SpriteSheet();
};
