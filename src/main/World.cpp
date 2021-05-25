#include "../headers/World.h"

World::World() 
{
  axis   = new Axis(AXIS_DISTANCE, AXIS_ACTIVE);
  camera = new Camera();
  ship   = new Ship();
  time   = new Time();
  wall   = new Wall(WALL_LIM, WALL_DIST, WALL_RATIO);
  
  ship->world   = this;
  camera->world = this;
}

World::~World() {
  delete axis;
  delete camera;
  delete ship;
  delete time;
  delete wall;
}