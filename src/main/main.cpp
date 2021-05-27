#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "../headers/Axis.h"
#include "../headers/EulerRotation.h"
#include "../headers/Mouse.h"
#include "../headers/Settings.h"
#include "../headers/Time.h"
#include "../headers/Util.h"
#include "../headers/Wall.h"
#include "../headers/World.h"

World*    world                       = new World();

AsteroidGenerator* asteroid_generator = world->asteroid_generator;
Axis*     axis                        = world->axis;
Lighting* lighting                    = world->lighting;
Mouse*    mouse                       = world->mouse;
Time*     game_time                   = world->time;
Wall*     wall                        = world->wall;
                  
Camera*   camera                      = world->camera;
Ship*     ship                        = world->ship;
Skybox*   skybox                      = world->skybox;

void render()
{
  game_time->tick();
  ship->tick();

  camera->place_camera();

  lighting->world_lighting();

  skybox->draw();

  ship->draw();  
  wall->draw();
  axis->draw();

  asteroid_generator->tick();

  ship->cannon->tick();

  game_time->update();
  glutSwapBuffers();
}

void on_idle()
{
  game_time->tick();
  
  wall->wall_distance_warning(ship->body->position);
  wall->update_wall_color();
  
  glutPostRedisplay();
  game_time->update();
}

void on_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  render();

  int err;
  
  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("Error: %s\n", gluErrorString(err));
  }
}

void on_reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  world->viewport_width = w;
  world->viewport_height = h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  if (w > h)
  {
    gluPerspective(CAMREA_FOV, w / h, 1, CAMREA_FAR);
  }
  else 
  {
    gluPerspective(CAMREA_FOV, h / w, 1, CAMREA_FAR);
  }
}

void on_key_press(unsigned char key, int x, int y)
{
  ship->on_key_press(key, x, y);

  if (key == KEY_ESC)
  {
    exit(EXIT_SUCCESS);
  }
}

void on_key_release(unsigned char key, int x, int y)
{
  ship->on_key_release(key, x, y);
}

void on_mouse_move(int x, int y)
{
  mouse->on_mouse_move(x, y);
}

void init_app(int *argcp, char **argv)
{
  glutInit(argcp, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(world->viewport_width, world->viewport_width);
  glutCreateWindow(GAME_TITLE);
  glutReshapeFunc(on_reshape);

  glutKeyboardFunc(on_key_press);
  glutKeyboardUpFunc(on_key_release);

  glutPassiveMotionFunc(on_mouse_move);

  glutDisplayFunc(on_display);
  glutIdleFunc(on_idle);

  glutFullScreen();

  lighting->init();
  camera->place_camera();
  
  skybox->load_skybox_textures();
  asteroid_generator->load_asteroid_textures();
  ship->load_ship_graphics();

  asteroid_generator->generate();
}

int main(int argc, char **argv)
{
  init_app(&argc, argv);
  glutMainLoop();
  return (EXIT_SUCCESS);
}