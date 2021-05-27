#include "../headers/Mouse.h"

Mouse::Mouse(World* world)
{
  position    = new Vector3(0, 0, 0);
  ratio       = new Vector3(0, 0, 0);
  this->world = world;
}

Mouse::~Mouse()
{
  delete position;
}

void Mouse::on_mouse_move(int x, int y)
{
  if (x >= 0 && x <= world->viewport_width && y >= 0 && y <= world->viewport_width)
  {
    position->x = x;
    position->y = y;

    update_move_vector();
  }
}

void Mouse::update_move_vector()
{
  ratio->x = (position->x - world->viewport_width/2) / (world->viewport_width/2);
  ratio->y = -(position->y - world->viewport_height/2) / (world->viewport_height/2);
}
