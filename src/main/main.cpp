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

World*    world     = new World();

Axis*     axis      = world->axis;
Lighting* lighting  = world->lighting;
Mouse*    mouse     = world->mouse;
Time*     game_time = world->time;
Wall*     wall      = world->wall;

Camera*   camera    = world->camera;
Ship*     ship      = world->ship;
Skybox*   skybox    = world->skybox;

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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 2000.0);
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

void init_app(int *argcp, char **argv)
{
  glutInit(argcp, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(VIEWPORT_DIM, VIEWPORT_DIM);
  glutCreateWindow(GAME_TITLE);
  glutReshapeFunc(on_reshape);

  glutKeyboardFunc(on_key_press);
  glutKeyboardUpFunc(on_key_release);

  glutDisplayFunc(on_display);
  glutIdleFunc(on_idle);

  lighting->init();
  camera->place_camera();
  skybox->load_skybox_textures();
  ship->load_ship_graphics();
}

int main(int argc, char **argv)
{
  init_app(&argc, argv);
  glutMainLoop();
  return (EXIT_SUCCESS);
}