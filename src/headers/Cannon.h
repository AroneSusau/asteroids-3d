#pragma once

#include <string>
#include <vector>

#include "Ship.h"
#include "RigidBody.h"
#include "Bullet.h"
#include "Vector3.h"
#include "V3_Math.h"

class Ship;
class World;
class Bullet;

class Cannon
{
  public:

    RigidBody* body;
    Ship* ship;
    World* world;
    Vector3* offset;
    std::vector<Bullet*>* bullets;

    bool active;

    float rate_of_fire;
    float next_fire;
    float bullet_velocity;

    std::string bullet_texture;
    int bullet_texture_id;

    Cannon();
    Cannon(Ship* ship, Vector3* position, Vector3* offset, World* world);
    ~Cannon();

    void tick();

    void fire();
    bool can_fire();

    void update_position();
    void update_fire_rate();

    void load_cannon_graphics();
};
