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
  wall               = new Wall(this, WALL_LINES, WALL_DIST, WALL_WARN_DIST);
  
  camera = new Camera();
  ship   = new Ship(this);
  skybox = new Skybox();
  
  camera->world = this;
  skybox->world = this;

  viewport_width = VIEWPORT_DIM;
  viewport_height = VIEWPORT_DIM;

  player_points = 0;
  player_death_time = 0;

  game_state = GAME_START;
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

void World::start_screen()
{
  Vector3 pos = Vector3(4489, 6061, 1751);

  camera->body->position->x = pos.x;
  camera->body->position->y = pos.y;
  camera->body->position->z = pos.z;

  gluLookAt(
    pos.x, pos.y, pos.z,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f);
}

void World::reset_game()
{
  player_points = 0;
  player_death_time = 0;
  
  time->delta = 0;
  time->time = 0;
  time->now = 0;

  game_state = GAME_PLAYING;

  ship->reset();
  asteroid_generator->reset();
  particle_generator->reset();

  asteroid_generator->debug_asteroid();

  glutSetCursor(GLUT_CURSOR_CROSSHAIR);
  glutWarpPointer(viewport_width / 2.0f, viewport_width / 2.0f);
}

void World::init()
{
  lighting->init();

  camera->place_camera();
  
  skybox->load_skybox_textures();
  asteroid_generator->load_asteroid_textures();
  particle_generator->load_textures();
  ship->load_ship_graphics();  
}