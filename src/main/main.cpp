#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

#include "../headers/tiny_obj_loader.h"

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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <iostream>

#include "../headers/World.h"
#include "../headers/Time.h"
#include "../headers/EulerRotation.h"
#include "../headers/Wall.h"
#include "../headers/Axis.h"

#include "../headers/Settings.h"

#define KEY_ESC 27

World* world = new World();

Camera* camera  = world->camera;
Ship* ship      = world->ship;
Time* game_time = world->time;
Wall* wall      = world->wall;
Axis* axis      = world->axis;

GLuint skybox [6] = {};

GLuint load_texture(const char* filename)
{
  int width, height, components;
  unsigned char *data; 
  GLuint id;

  data = stbi_load(filename, &width, &height, &components, STBI_rgb);
  glPushAttrib(GL_TEXTURE_BIT);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  free(data);
  glPopAttrib();

  return id;
}

void render()
{
  game_time->tick();
  
  ship->update_position();
  camera->place_camera();

  GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

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
  gluPerspective(45.0, 1.0, 1.0, 1000.0);
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
  glutInitWindowSize(800, 800);
  glutCreateWindow("Asteroids Assignment 2");
  glutReshapeFunc(on_reshape);

  glutKeyboardFunc(on_key_press);
  glutKeyboardUpFunc(on_key_release);

  glutDisplayFunc(on_display);
  glutIdleFunc(on_idle);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_LIGHTING);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_NORMALIZE);

  float ambient0[] = {1.0, 1.0, 1.0, 1.0};
  float diffuse0[] = {1.0, 1.0, 1.0, 1.0};
  float specular0[] = {1.0, 1.0, 1.0, 1.0};

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_LIGHTING);
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
  glEnable(GL_LIGHT0);

  camera->place_camera();
}

int main(int argc, char **argv)
{
  init_app(&argc, argv);
  glutMainLoop();
  return (EXIT_SUCCESS);
}