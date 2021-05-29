#include "../headers/Particle.h"

Particle::Particle(World* world, SpriteSheet* sheet, int texture, float size)
{
  this->world    = world;
  this->body     = new RigidBody();
  this->animator = new Animator(world, sheet);
  this->velocity = new Vector3(0, 0, 0);
  this->texture  = texture;
  this->size     = size;
}

Particle::~Particle()
{
  delete body;
  delete velocity;
  delete animator;
}

void Particle::tick() 
{
  body->update_forward(V3_Math::normalize(V3_Math::subtract(world->ship->body->position, body->position)));
  body->update_up(world->ship->body->up);
  body->update_right(V3_Math::cross(body->forward, body->up));
  body->update_position(V3_Math::add(body->position, V3_Math::multiply(velocity, world->time->delta)));
}

void Particle::draw() 
{
  glPushMatrix();
    glDisable(GL_LIGHTING);
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);

    glScalef(size, size, size);

    float matrix [] = {
      body->right->x,    body->right->y,    body->right->z,    0.0f,              
      body->up->x,       body->up->y,       body->up->z,       0.0f,
      body->forward->x,  body->forward->y,  body->forward->z,  0.0f,
      body->position->x, body->position->y, body->position->z, 1.0f
    };

    glMultMatrixf(matrix);

    glBegin(GL_QUADS);

    glEnd();

    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
  glPopMatrix();
}
