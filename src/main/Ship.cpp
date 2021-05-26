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
  rotation = new Vector3(0, 0, 0);
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
  delete rotation;
}

void Ship::draw()
{
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);

  Materials::ship();
  glBindTexture(GL_TEXTURE_2D, ship_id);

  float matrix [] = {
    body->right->x,    body->right->y,    body->right->z,    0.0f,
    -body->forward->x, -body->forward->y, -body->forward->z, 0.0f,              
    -body->up->x,      -body->up->y,      -body->up->z,      0.0f,
    body->position->x, body->position->y, body->position->z, 1.0f
  };

  glMultMatrixf(matrix);
  glRotatef(35 * world->mouse->ratio->y, 1, 0, 0);
  glRotatef(-35 * world->mouse->ratio->x, 0, 1, 0);

  glBegin(GL_TRIANGLES);
  
  for (size_t i = 0; i < model.size; ++i)
  {
      glTexCoord2f(model.tx.at(i), model.ty.at(i));
      glNormal3f(model.nx.at(i), model.ny.at(i), model.nz.at(i));
      glVertex3f(model.vx.at(i), model.vy.at(i), model.vz.at(i));
  }

  glEnd();
  glDisable(GL_TEXTURE_2D);

  drawWings();
  glPopMatrix();
}

void Ship::drawWings()
{
  
  Materials::brass();
  glPushMatrix();
  glRotatef(-12, 1, 0, 0);
    glRotatef(-25, 0, 1, 0);
    glPushMatrix();
      glTranslatef(2.9 * animation, -0.2, -0.2);
      glScalef(4.0 * animation, 0.7 * animation, 0.05);
      glutSolidCube(1.0);
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glRotatef(-12, 1, 0, 0);
    glRotatef(25, 0, 1, 0);
    glPushMatrix();
      glTranslatef(-2.9 * animation, -0.2, -0.2);
      glScalef(-4.0 * animation, -0.7 * animation, -0.05);
      glutSolidCube(1.0);
    glPopMatrix();
  glPopMatrix();

  Materials::jade();
  glPushMatrix();
  glRotatef(-4, 1, 0, 0);
    glRotatef(13, 0, 1, 0);
    glPushMatrix();
      glTranslatef(2.0 * animation, 0.0, 0.0);
      glScalef(4.0 * animation, 0.4 * animation, 0.05);
      glutSolidCube(1.0);
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
  glRotatef(-4, 1, 0, 0);
    glRotatef(-13, 0, 1, 0);
    glPushMatrix();
      glTranslatef(-2.0 * animation, 0.0, 0.0);
      glScalef(-4.0 * animation, -0.4 * animation, -0.05);
      glutSolidCube(1.0);
    glPopMatrix();
  glPopMatrix();
}

void Ship::load_ship_graphics()
{
  ship_id = Util::load_texture(texture_path.c_str());
  Util::load_model(model_filename.c_str(), material_path.c_str(), model);
}

void Ship::update_velocity() 
{
  velocity->x += can_accelerate(body->advance, INCREASE, velocity->x, MAX_ADVANCE) ? acceleration->x : 0;
  velocity->x -= can_accelerate(body->advance, DECREASE, velocity->x, 0) ? acceleration->x : 0;

  velocity->y += can_accelerate(body->strafe, INCREASE, velocity->y, MAX_STRAFE) ? acceleration->y : 0;
  velocity->y -= can_accelerate(body->strafe, DECREASE, velocity->y, MAX_STRAFE) ? acceleration->y : 0;

  if (body->roll == INCREASE && rotation->x > -MAX_ROLL)
  {
    rotation->x -= acceleration->x;
  }

  if (body->roll == DECREASE && rotation->x < MAX_ROLL)
  {
    rotation->x += acceleration->x;
  }

  rotation->y += world->mouse->ratio->y * MAX_PITCH;
  rotation->z -= world->mouse->ratio->x * MAX_YAW;
}

void Ship::update_position()
{
  EulerRotation::advance(body, velocity->x * world->time->delta);
  EulerRotation::strafe(body, velocity->y * world->time->delta);

  EulerRotation::roll(body, rotation->x * world->time->delta);
  EulerRotation::pitch(body, rotation->y * world->time->delta);
  EulerRotation::yaw(body, rotation->z * world->time->delta);

  body->update_look(V3_Math::add(body->position, body->forward));
}

void Ship::update_animation()
{
  animation = velocity->x / MAX_ADVANCE;
}

bool Ship::can_accelerate(move_state_t state, move_state_t expected, float velocity, float clamp)
{
  return (
    (expected == INCREASE && state == expected && velocity < clamp) || 
    (expected == DECREASE && state == expected && velocity > -clamp)
  );
}

void Ship::decelerate()
{

  if (body->strafe == NEUTRAL)
  {
    velocity->y *= STRAFE_DECELERATION;
  }

  if (body->roll == NEUTRAL)
  {
    rotation->x *= ROLL_DECELERATION;
  }

  if (body->pitch == NEUTRAL)
  {
    rotation->y *= PITCH_DECELERATION;
  }

  if (body->yaw == NEUTRAL)
  {
    rotation->z *= YAW_DECELERATION;
  }
}

void Ship::tick()
{
  update_velocity();
  update_position();
  update_animation();
  decelerate();
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