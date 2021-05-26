#include "../headers/Axis.h"

Axis::Axis(float distance, bool active) 
{
  this->distance = distance;
  this->active   = active;
}

Axis::~Axis() {}

void Axis::draw()
{
  if (active)
  {
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(-distance, 0, 0);
      glVertex3f(distance, 0, 0);

      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0, -distance, 0);
      glVertex3f(0, distance, 0);

      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0, 0, -distance);
      glVertex3f(0, 0, distance);
    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
  }
}