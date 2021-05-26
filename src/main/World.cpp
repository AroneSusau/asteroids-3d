#include "../headers/World.h"

World::World() 
{
  axis     = new Axis(AXIS_DISTANCE, AXIS_ACTIVE);
  lighting = new Lighting();
  time     = new Time();
  wall     = new Wall(WALL_LINES, WALL_DIST, WALL_WARN_DIST);
  
  camera = new Camera();
  ship   = new Ship();
  skybox = new Skybox();
  
  ship->world   = this;
  camera->world = this;
  skybox->world = this;
}

World::~World() {
  delete axis;
  delete camera;
  delete lighting;
  delete ship;
  delete skybox;
  delete time;
  delete wall;
}