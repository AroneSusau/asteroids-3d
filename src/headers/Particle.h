#pragma once

#include "World.h"
#include "RigidBody.h"
#include "SpriteSheet.h"
#include "Animator.h"

class World;
class RigidBody;
class Animator;
class SpriteSheet;

class Particle
{
  public:

    World* world;
    RigidBody* body;
    Vector3* velocity;
    Animator* animator;

    int texture;
    float size;

    Particle(World* world, SpriteSheet* sheet, int texture, float size);
    ~Particle();

    void draw();
    void tick();
};
