#include "../headers/Ship.h"

Ship::Ship(World* world) 
{
  body = new RigidBody();
  this-> world = world;

  body->update_position(new Vector3( 0, 0, 0));
  body->update_forward(new Vector3( 0, 0, -1));
  body->update_up(new Vector3( 0, 1,  0));
  body->update_right(new Vector3(1, 0,  0));
  body->update_look(new Vector3( 0, 0, -100));

  velocity     = new Vector3(0, 0, 0);
  rotation     = new Vector3(0, 0, 0);
  look         = new Vector3(0, 0, 0);
  acceleration = new Vector3(ADVANCE_ACCEL, STRAFE_ACCEL, 0);

  cannon = new Cannon(this, body->position, new Vector3(0, 0, 0), world);

  active = false;

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
  delete look;
  delete cannon;
}

void Ship::draw()
{
  if (active)
  {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, ship_id);

    ship_forward_rotation();
    
    if (world->game_state == GAME_PLAYING)
    {
      mouse_ship_rotation();
    }
    
    draw_ship();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glDisable(GL_CULL_FACE);
  }
}

void Ship::draw_ship()
{
  Materials::ship();
  glBegin(GL_TRIANGLES);
  
  for (size_t i = 0; i < model.size; ++i)
  {
    glTexCoord2f(model.tx.at(i), model.ty.at(i));
    glNormal3f(model.nx.at(i), model.ny.at(i), model.nz.at(i));
    glVertex3f(model.vx.at(i), model.vy.at(i), model.vz.at(i));
  }

  glEnd();

  glPushAttrib(GL_CURRENT_BIT);
  Materials::wings();

  glPushMatrix();
    glTranslatef(0, 0, 0.2 * world->mouse->ratio->y);
    glTranslatef(1.84f, 1.4f, 0.4f);
    glRotatef(-6, 0, 1, 0);
    glRotatef(50 * world->mouse->ratio->y, 1, 0, 0);
    glScalef(1.1f, 0.6f, 0.1f);
    glColor3f(0.74f, 0.22f, 0.43f);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, 0.2 * world->mouse->ratio->y);
    glTranslatef(-1.84f, 1.4f, 0.4f);
    glRotatef(6, 0, 1, 0);
    glRotatef(50 * world->mouse->ratio->y, 1, 0, 0);
    glScalef(1.1f, 0.6f, 0.1f);
    glColor3f(0.74f, 0.22f, 0.43f);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.2f, 2.5f, 0.3f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.24 * world->mouse->ratio->x, 2.3f, 0);
    glRotatef(70 * world->mouse->ratio->x, 0, 0, 1);
    glScalef(0.1, 0.5, 0.9);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCube(1);
  glPopMatrix();
  glPopAttrib();
}

void Ship::mouse_ship_rotation()
{
  glRotatef(look->y, 1, 0, 0);
  glRotatef(-look->z, 0, 1, 0);
  glRotatef(look->x, 0, 0, 1);
}

void Ship::ship_forward_rotation()
{
  float matrix [] = {
    body->right->x,    body->right->y,    body->right->z,    0.0f,
    -body->forward->x, -body->forward->y, -body->forward->z, 0.0f,              
    -body->up->x,      -body->up->y,      -body->up->z,      0.0f,
    body->position->x, body->position->y, body->position->z, 1.0f
  };

  glMultMatrixf(matrix);
}

void Ship::load_ship_graphics()
{
  ship_id = Util::load_texture(texture_path.c_str(), true);
  
  cannon->load_cannon_graphics();
  
  Util::load_model(model_filename.c_str(), material_path.c_str(), model);
}

void Ship::update_velocity() 
{
  velocity->x += can_accelerate(body->advance, INCREASE, velocity->x, MAX_ADVANCE) ? acceleration->x : 0;
  velocity->x -= can_accelerate(body->advance, DECREASE, velocity->x, 0) ? acceleration->x * 0.5 : 0;

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
  if (active && world->game_state == GAME_PLAYING)
  {
    EulerRotation::advance(body, velocity->x * world->time->delta);
    EulerRotation::strafe(body, velocity->y * world->time->delta);

    EulerRotation::roll(body, rotation->x * world->time->delta);
    EulerRotation::pitch(body, rotation->y * world->time->delta);
    EulerRotation::yaw(body, rotation->z * world->time->delta);

    body->update_look(V3_Math::add(body->position, body->forward));
  }
}

void Ship::update_animation()
{
  animation = velocity->x / MAX_ADVANCE;
}

void Ship::update_look()
{
  look->x += SHIP_LOOK_ACCEL * (world->mouse->ratio->x < 0 ? -1 : 1);
  look->y += SHIP_LOOK_ACCEL * (world->mouse->ratio->y < 0 ? -1 : 1);
  look->z += SHIP_LOOK_ACCEL * (world->mouse->ratio->x < 0 ? -1 : 1);

  float x_max = SHIP_LOOK_X * world->mouse->ratio->x;
  float y_max = SHIP_LOOK_Y * world->mouse->ratio->y;
  float z_max = SHIP_LOOK_Z * world->mouse->ratio->x;

  if (world->mouse->ratio->x > 0)
  {
    look->z = look->z > z_max ? z_max : look->z;
    look->x = look->x > x_max ? x_max : look->x;
  }
  else
  {
    look->z = look->z < z_max ? z_max : look->z;
    look->x = look->x < x_max ? x_max : look->x;
  }

  if (world->mouse->ratio->y > 0)
  {
    look->y = look->y > y_max ? y_max : look->y;
  }
  else
  {
    look->y = look->y < y_max ? y_max : look->y;
  }
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

  if (body->advance == NEUTRAL)
  {
    velocity->x *= ADVANCE_DECELERATION;
  }

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
  if (active)
  {
    update_velocity();
    update_position();
    update_animation();
    update_look();
    decelerate();

    cannon->tick();

    shoot();
  }
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
    case ' ':
      firing = true;
      break;
    default:
      break;
  }
}

void Ship::shoot()
{
  if (firing && cannon->can_fire())
  {
    cannon->fire();
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
    case ' ':
      firing = false;
      break;
  }
}

void Ship::reset()
{ 
  body->update_position(new Vector3( 0, 0, 0));
  body->update_forward(new Vector3( 0, 0, -1));
  body->update_up(new Vector3( 0, 1,  0));
  body->update_right(new Vector3(1, 0,  0));
  body->update_look(new Vector3( 0, 0, -100));

  velocity     = new Vector3(0, 0, 0);
  rotation     = new Vector3(0, 0, 0);
  look         = new Vector3(0, 0, 0);
  acceleration = new Vector3(ADVANCE_ACCEL, STRAFE_ACCEL, 0);

  active = true;
  
  EulerRotation::yaw(body, 1);
  EulerRotation::yaw(body, -1);
}
