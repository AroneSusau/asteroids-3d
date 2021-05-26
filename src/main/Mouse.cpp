#include "../headers/Ship.h"

Mouse::Mouse()
{
  position = new Vector3(0, 0, 0);
  ratio    = new Vector3(0, 0, 0);
}

Mouse::~Mouse()
{
  delete position;
}

void Mouse::on_mouse_move(int x, int y)
{
  if (x >= 0 && x <= VIEWPORT_DIM && y >= 0 && y <= VIEWPORT_DIM)
  {
    position->x = x;
    position->y = y;

    update_move_vector();
  }
}

void Mouse::update_move_vector()
{
  ratio->x = (position->x - VIEWPORT_DIM/2) / (VIEWPORT_DIM/2);
  ratio->y = -(position->y - VIEWPORT_DIM/2) / (VIEWPORT_DIM/2);
}
