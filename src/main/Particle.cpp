#include "../headers/Particle.h"

Particle::Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime)
{
  this->world         = world;
  this->body          = new RigidBody();
  this->animator      = new Animator(world, sheet);
  this->velocity      = new Vector3(0, 0, 0);
  this->texture       = texture;
  this->original_size = 0.f;
  this->size          = size;
  this->finished      = false;
  this->runtime       = runtime;
  this->time_count    = 0.0f;
  this->countdown     = 0.0f;
  this->shrinks       = false;
}

Particle::Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime, float countdown)
{
  this->world         = world;
  this->body          = new RigidBody();
  this->animator      = new Animator(world, sheet);
  this->velocity      = new Vector3(0, 0, 0);
  this->texture       = texture;
  this->original_size = 0.f;
  this->size          = size;
  this->finished      = false;
  this->runtime       = runtime;
  this->time_count    = 0.0f;
  this->countdown     = countdown;
  this->shrinks       = false;
}

Particle::Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime, float countdown, bool shrinks)
{
  this->world         = world;
  this->body          = new RigidBody();
  this->animator      = new Animator(world, sheet);
  this->velocity      = new Vector3(0, 0, 0);
  this->texture       = texture;
  this->original_size = size;
  this->size          = size;
  this->finished      = false;
  this->runtime       = runtime;
  this->time_count    = countdown;
  this->countdown     = countdown;
  this->shrinks       = shrinks;
}

Particle::~Particle()
{
  delete body;
  delete velocity;
  delete animator;
}

void Particle::tick() 
{
  animator->update_frame();
  isFinished();

  if (shrinks)
  {
    update_shrink();
  }

  body->update_forward(V3_Math::normalize(V3_Math::subtract(world->camera->body->position, body->position)));
  body->update_up(world->camera->body->up);
  body->update_right(V3_Math::cross(body->forward, body->up));
  
  body->update_position(V3_Math::add(body->position, V3_Math::multiply(velocity, world->time->delta)));

  countdown -= world->time->delta;
}

void Particle::draw() 
{
  glPushMatrix();
  glPushAttrib(GL_CURRENT_BIT);

    glDisable(GL_LIGHTING);
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);

    float matrix [] = {
      body->right->x,    body->right->y,    body->right->z,    0.0f,              
      body->up->x,       body->up->y,       body->up->z,       0.0f,
      body->forward->x,  body->forward->y,  body->forward->z,  0.0f,
      body->position->x, body->position->y, body->position->z, 1.0f
    };

    glMultMatrixf(matrix);

    glScalef(size, size, size);

    glBegin(GL_QUADS);
    
      std::vector<Vector3*>* frame = animator->frames->at(animator->current_frame);
      
      glNormal3f(body->forward->x, body->forward->y, body->forward->z);
      glTexCoord2f(frame->at(0)->x, frame->at(0)->y);
      glVertex3f(-size, -size, 0);

      glTexCoord2f(frame->at(1)->x, frame->at(1)->y);
      glVertex3f(size, -size, 0);

      glTexCoord2f(frame->at(2)->x, frame->at(2)->y);
      glVertex3f(size, size, 0);

      glTexCoord2f(frame->at(3)->x, frame->at(3)->y);
      glVertex3f(-size, size, 0);
    
    glEnd();

    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
  glPopAttrib();
  glPopMatrix();
}

void Particle::isFinished()
{
  if (runtime == PARTICLE_FRAME)
  {
    finished = animator->current_frame >= animator->sheet->frame_end;
  }
  else if (runtime == PARTICLE_TIME)
  {
    finished = countdown <= 0;
  }
}

void Particle::update_shrink()
{
  if (PARTICLE_FRAME)
  {
    size = original_size * animator->current_frame / animator->sheet->frame_end;
  }
  else if (PARTICLE_TIME)
  {
    size = original_size * countdown / time_count;
  }
}