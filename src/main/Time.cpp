#include "../headers/Time.h"

Time::Time() 
{}

Time::~Time() 
{}

void Time::tick()
{
  now = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
  delta = now - time;
}

void Time::update()
{
  time = now;
}