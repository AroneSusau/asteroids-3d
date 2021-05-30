#include "../headers/World.h"

World::World() 
{
  asteroid_generator = new AsteroidGenerator(this);
  axis               = new Axis(AXIS_DISTANCE, AXIS_ACTIVE);
  hud                = new HUD(this);
  lighting           = new Lighting();
  mouse              = new Mouse(this);
  particle_generator = new ParticleGenerator(this);
  time               = new Time();
  wall               = new Wall(WALL_LINES, WALL_DIST, WALL_WARN_DIST);
  
  camera = new Camera();
  ship   = new Ship(this);
  skybox = new Skybox();
  
  camera->world = this;
  skybox->world = this;

  viewport_width = VIEWPORT_DIM;
  viewport_height = VIEWPORT_DIM;

  player_points = 0;
  player_death_time = 0;

  game_state = GAME_PLAYING;
}

World::~World() {
  delete asteroid_generator;
  delete axis;
  delete camera;
  delete hud;
  delete lighting;
  delete mouse;
  delete ship;
  delete skybox;
  delete time;
  delete wall;
}