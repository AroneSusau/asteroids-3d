#include "../headers/Bullet.h"

Bullet::Bullet()
{
  body          = new RigidBody();
  velocity      = new Vector3();
  size          = BULLET_SIZE;
  out_of_bounds = false;
  collide       = false;
}

Bullet::Bullet(World* world, Vector3* position, Vector3* velocity, int texture)
{
  this->body     = new RigidBody();
  this->velocity = velocity;
  this->world    = world;
  this->texture  = texture;

  size = BULLET_SIZE;
  out_of_bounds = false;

  animator = new Animator(world, BULLET_TEXTURE_ROWS, BULLET_TEXTURE_COLS, BULLET_START_FRAME, BULLET_END_FRAME);

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
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  float matrix [] = {
    body->right->x,    body->right->y,    body->right->z,    0.0f,              
    body->up->x,       body->up->y,       body->up->z,       0.0f,
    body->forward->x,  body->forward->y,  body->forward->z,  0.0f,
    body->position->x, body->position->y, body->position->z, 1.0f
  };

  glMultMatrixf(matrix);

  glColor3f(1, 1, 1);

  glEnable (GL_BLEND);
  glDepthMask (GL_FALSE);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE);

  glBegin(GL_QUADS);
    
    std::vector<Vector3*>* frame = animator->frames->at(animator->current_frame);
    
    glNormal3f(body->forward->x, body->forward->y, body->forward->z);
    glTexCoord2f(frame->at(0)->x, frame->at(0)->y);
    glVertex3f(-BULLET_SIZE, -BULLET_SIZE, 0);

    glTexCoord2f(frame->at(1)->x, frame->at(1)->y);
    glVertex3f(BULLET_SIZE, -BULLET_SIZE, 0);

    glTexCoord2f(frame->at(2)->x, frame->at(2)->y);
    glVertex3f(BULLET_SIZE, BULLET_SIZE, 0);

    glTexCoord2f(frame->at(3)->x, frame->at(3)->y);
    glVertex3f(-BULLET_SIZE, BULLET_SIZE, 0);
    
  glEnd();
  glDepthMask (GL_TRUE);
  glDisable (GL_BLEND);

  glPopMatrix();
  glPopAttrib();
  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
}

void Bullet::tick() 
{
  update_position();
  animator->update_frame();
  check_bounds();
}

void Bullet::update_position() 
{
  body->position->x += velocity->x * world->time->delta;
  body->position->y += velocity->y * world->time->delta;
  body->position->z += velocity->z * world->time->delta;

  EulerRotation::roll(body, BULLET_ROTATION * world->time->delta);
}

void Bullet::check_bounds()
{
  out_of_bounds = (
    body->position->x <= -WALL_TOTAL_DIST || body->position->x >= WALL_TOTAL_DIST ||
    body->position->y <= -WALL_TOTAL_DIST || body->position->y >= WALL_TOTAL_DIST ||
    body->position->z <= -WALL_TOTAL_DIST || body->position->z >= WALL_TOTAL_DIST
  );
}
