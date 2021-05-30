#pragma once

#include "World.h"
#include "RigidBody.h"
#include "SpriteSheet.h"
#include "Animator.h"

class World;
class RigidBody;
class Animator;
class SpriteSheet;

typedef enum { PARTICLE_FRAME, PARTICLE_TIME } particle_runtime_t;

class Particle
{
  public:

    World* world;
    RigidBody* body;
    Vector3* velocity;
    Animator* animator;
    particle_runtime_t runtime;

    int texture;
    
    float size;
    float original_size;

    float time_count;
    float countdown;

    bool finished;
    bool shrinks;

    Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime);
    Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime, float countdown);
    Particle(World* world, SpriteSheet* sheet, int texture, float size, particle_runtime_t runtime, float countdown, bool shrinks);
    ~Particle();

    void draw();
    void tick();

    void isFinished();
    void update_shrink();
};
