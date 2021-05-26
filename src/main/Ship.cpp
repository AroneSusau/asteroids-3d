#include "../headers/Ship.h"

Ship::Ship() 
{
  body = new RigidBody();

  body->update_position(new Vector3( 0, 0, 0));
  body->update_forward(new Vector3( 0, 0, -1));
  body->update_up(new Vector3( 0, 1,  0));
  body->update_right(new Vector3(1, 0,  0));
  body->update_look(new Vector3( 0, 0, -100));

  velocity = new Vector3(0, 0, 0);
  acceleration = new Vector3(ADVANCE_ACCEL, STRAFE_ACCEL, 0);

  model_filename = SHIP_MODEL_PATH;
  material_path  = SHIP_MATERIAL_PATH;
  texture_path   = SHIP_TEXTURE_PATH; 
  
  EulerRotation::yaw(body, 1);
  EulerRotation::yaw(body, -1);
}

Ship::~Ship() 
{
  delete body;
  delete velocity;
  delete acceleration;
}

void Ship::draw()
{
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);

  float mat_diffuse[] = { 0.8, 0.8, 0.0, 1.0 };
  float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  float mat_shininess[] = { 100.0 };

  // setup materials
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture(GL_TEXTURE_2D, ship_id);

  float matrix [] = {
    body->right->x,    body->right->y,    body->right->z,    0.0f,
    -body->forward->x, -body->forward->y, -body->forward->z, 0.0f,              
    -body->up->x,      -body->up->y,      -body->up->z,      0.0f,
    body->position->x, body->position->y, body->position->z, 1.0f
  };

  glMultMatrixf(matrix);

  glBegin(GL_TRIANGLES);
  
  for (size_t i = 0; i < model.size; ++i)
  {
      glNormal3f(model.nx.at(i), model.ny.at(i), model.nz.at(i));
      glTexCoord2f(model.tx.at(i), model.ty.at(i));
      glVertex3f(model.vx.at(i), model.vy.at(i), model.vz.at(i));
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void Ship::load_ship_graphics()
{
  ship_id = Util::load_texture(texture_path.c_str());
  Util::load_model(model_filename.c_str(), material_path.c_str(), model);
}

void Ship::update_position()
{
  if (body->advance == INCREASE)
  {
    EulerRotation::advance(body, MAX_ADVANCE * world->time->delta);
  }
  
  if (body->advance == DECREASE)
  {
    EulerRotation::advance(body, -MAX_ADVANCE * world->time->delta);
  }
  
  if (body->strafe == INCREASE)
  {
    EulerRotation::strafe(body, MAX_STRAFE * world->time->delta);
  }
  
  if (body->strafe == DECREASE)
  {
    EulerRotation::strafe(body, -MAX_STRAFE * world->time->delta);
  }

  if (body->pitch == INCREASE)
  {
    EulerRotation::pitch(body, MAX_ROTATION * world->time->delta);
  }

  if (body->pitch == DECREASE)
  {
    EulerRotation::pitch(body, -MAX_ROTATION * world->time->delta);
  }

  if (body->yaw == INCREASE)
  {
    EulerRotation::yaw(body, -MAX_ROTATION * world->time->delta);
  }

  if (body->yaw == DECREASE)
  {
    EulerRotation::yaw(body, MAX_ROTATION * world->time->delta);
  }

  if (body->roll == INCREASE)
  {
    EulerRotation::roll(body, -MAX_ROTATION * world->time->delta);
  }

  if (body->roll == DECREASE)
  {
    EulerRotation::roll(body, MAX_ROTATION * world->time->delta);
  }

  body->update_look(V3_Math::add(body->position, body->forward));
}

void Ship::on_key_press(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 'A':
    case 'a':
      body->strafe = DECREASE;
      break;
    case 'D':
    case 'd':
      body->strafe = INCREASE;
      break;
    case 'W':
    case 'w':
      body->advance = INCREASE;
      break;
    case 'S':
    case 's':
      body->advance = DECREASE;
      break;
    case 'i':
    case 'I':
      body->pitch = INCREASE;
      break;
    case 'k':
    case 'K':
      body->pitch = DECREASE;
      break;
    case 'j':
    case 'J':
      body->yaw = DECREASE;
      break;
    case 'l':
    case 'L':
      body->yaw = INCREASE;
      break;
    case 'q':
    case 'Q':
      body->roll = DECREASE;
      break;
    case 'e':
    case 'E':
      body->roll = INCREASE;
      break;
    default:
      break;
  }
}

void Ship::on_key_release(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'A':
    case 'a':
      body->strafe = NEUTRAL;
      break;
    case 'D':
    case 'd':
      body->strafe = NEUTRAL;
      break;
    case 'W':
    case 'w':
      body->advance = NEUTRAL;
      break;
    case 'S':
    case 's':
      body->advance = NEUTRAL;
      break;
    case 'i':
    case 'I':
      body->pitch = NEUTRAL;
      break;
    case 'k':
    case 'K':
      body->pitch = NEUTRAL;
      break;
    case 'j':
    case 'J':
      body->yaw = NEUTRAL;
      break;
    case 'l':
    case 'L':
      body->yaw = NEUTRAL;
      break;
    case 'q':
    case 'Q':
      body->roll = NEUTRAL;
      break;
    case 'e':
    case 'E':
      body->roll = NEUTRAL;
      break;
  }
}