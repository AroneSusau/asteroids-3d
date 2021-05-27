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

typedef struct
{
  Vector3 position;
  Vector3 velocity;
} bullet_t;

std::vector<bullet_t> bullets;

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

  for (bullet_t& b : bullets)
  {
    b.position.x += b.velocity.x * game_time->delta; 
    b.position.y += b.velocity.y * game_time->delta; 
    b.position.z += b.velocity.z * game_time->delta;

    glPushMatrix();
    glTranslatef(b.position.x, b.position.y, b.position.z);
    glColor3f(1, 1, 1);
    glScalef(2, 2, 2);
    glutSolidCube(2.0);
    glPopMatrix();
  }

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
  gluPerspective(CAMREA_FOV, 1.0, 1.0, CAMREA_FAR);
}

bullet_t b;

void on_key_press(unsigned char key, int x, int y)
{
  ship->on_key_press(key, x, y);

  if (key == ' ')
  {
    b.position = *V3_Math::add(ship->body->position, V3_Math::multiply(ship->body->forward, 5));
    b.velocity = *V3_Math::add(V3_Math::multiply(ship->body->forward, ship->velocity->x), V3_Math::multiply(ship->body->forward, 7000));

    bullets.push_back(b);
  }

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
  glutInitWindowSize(VIEWPORT_DIM, VIEWPORT_DIM);
  glutCreateWindow(GAME_TITLE);
  glutReshapeFunc(on_reshape);

  glutKeyboardFunc(on_key_press);
  glutKeyboardUpFunc(on_key_release);

  glutPassiveMotionFunc(on_mouse_move);

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