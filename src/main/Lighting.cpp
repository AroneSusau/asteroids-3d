#include "../headers/Lighting.h"

Lighting::Lighting() 
{}

Lighting::~Lighting() 
{}

void Lighting::init() 
{
  glEnable(GL_LIGHTING);
  glEnable (GL_BLEND);
  glEnable (GL_LINE_SMOOTH);
  glEnable(GL_NORMALIZE);
  
  if (ENABLE_FOG)
  {
    fog();
  }

  glShadeModel(GL_SMOOTH); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Lighting::world_lighting() 
{
  if (LIGHTING_DEBUG)
  {
    debug_lighting();
  }
  else {
    GLfloat light_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = LIGHTING_POSITION;

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
  }
}

void Lighting::debug_lighting() {
  GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = LIGHTING_POSITION;

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
}

void Lighting::fog()
{
  glEnable(GL_FOG);
  glFogi (GL_FOG_MODE, GL_LINEAR);
  glFogf (GL_FOG_START, FOG_START);
  glFogf (GL_FOG_END, FOG_END);
  glHint (GL_FOG_HINT, GL_NICEST);
}

void Lighting::ship_lighting(Ship* ship)
{
  Vector3* pos = V3_Math::add(ship->body->position, V3_Math::multiply(ship->body->forward, 4));
  
  GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_position[] = { pos->x, pos->y, pos->z };;
  GLfloat spot_direction[] = {ship->body->forward->x, ship->body->forward->y, ship->body->forward->z};;

  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0);
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

  glEnable(GL_LIGHT1);
}
