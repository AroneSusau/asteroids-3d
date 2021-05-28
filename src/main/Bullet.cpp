#include "../headers/Bullet.h"

Bullet::Bullet()
{
  body     = new RigidBody();
  velocity = new Vector3();
  
  size = BULLET_SIZE;

  out_of_bounds = false;
  collide       = false;
}

Bullet::Bullet(World* world, Vector3* position, Vector3* velocity, int texture)
{
  this->body     = new RigidBody();
  this->velocity = velocity;
  this->world    = world;
  this->texture = texture;

  size = BULLET_SIZE;

  out_of_bounds = false;

  body->update_position(position);
}

Bullet::~Bullet()
{
  delete body;
  delete velocity;
}

void Bullet::draw() 
{
  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT);
  glDisable(GL_LIGHTING);

  GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 0.6 };
  GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0.6 };
  GLfloat mat_transparent[] = { 1.0, 1.0, 1.0, 0.6 };
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  float matrix [] = {
    body->right->x,    body->right->y,    body->right->z,    0.0f,              
    body->up->x,       body->up->y,       body->up->z,      0.0f,
    body->forward->x,  body->forward->y,  body->forward->z, 0.0f,
    body->position->x, body->position->y, body->position->z, 1.0f
  };

  glMultMatrixf(matrix);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glColor3f(1, 1, 1);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);

  glBegin(GL_QUADS);
    glNormal3f(body->forward->x, body->forward->y, body->forward->z);

    glTexCoord2f(0, 0);
    glVertex3f(-BULLET_SIZE, -BULLET_SIZE, 0);

    glTexCoord2f(1, 0);
    glVertex3f(BULLET_SIZE, -BULLET_SIZE, 0);

    glTexCoord2f(1, 1);
    glVertex3f(BULLET_SIZE, BULLET_SIZE, 0);

    glTexCoord2f(0, 1);
    glVertex3f(-BULLET_SIZE, BULLET_SIZE, 0);
  glEnd();

  glPopMatrix();
  glPopAttrib();
  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
}

void Bullet::tick() 
{
  update_position();
  check_bounds();
}

void Bullet::update_position() 
{
  body->position->x += velocity->x * world->time->delta;
  body->position->y += velocity->y * world->time->delta;
  body->position->z += velocity->z * world->time->delta;
}

void Bullet::check_bounds()
{
  out_of_bounds = (
    body->position->x <= -WALL_TOTAL_DIST || body->position->x >= WALL_TOTAL_DIST ||
    body->position->y <= -WALL_TOTAL_DIST || body->position->y >= WALL_TOTAL_DIST ||
    body->position->z <= -WALL_TOTAL_DIST || body->position->z >= WALL_TOTAL_DIST
  );
}
