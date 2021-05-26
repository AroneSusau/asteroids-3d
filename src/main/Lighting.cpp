#include "../headers/Lighting.h"

Lighting::Lighting() 
{}

Lighting::~Lighting() 
{}

void Lighting::init() 
{
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_LIGHTING);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_NORMALIZE);

  float ambient0[] = {1.0, 1.0, 1.0, 1.0};
  float diffuse0[] = {1.0, 1.0, 1.0, 1.0};
  float specular0[] = {1.0, 1.0, 1.0, 1.0};

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glShadeModel(GL_SMOOTH); 
  glEnable(GL_LIGHTING);
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
  glEnable(GL_LIGHT0);
}

void Lighting::world_lighting() 
{
  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
}
