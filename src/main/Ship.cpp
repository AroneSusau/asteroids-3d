#include "../headers/Ship.h"

Ship::Ship() 
{
  body = new RigidBody();
}

Ship::~Ship() 
{
  delete body;
}