#pragma once

#include "World.h"
#include "RigidBody.h"
#include "Util.h"
#include "Settings.h"

class World;

class Ship
{
  public:

    World* world;
    RigidBody* body;
    
    Vector3* velocity;
    Vector3* acceleration;

    model_vertex model;

    std::string model_filename;
    std::string material_path;
    std::string texture_path;
    int ship_id;

    Ship();
    ~Ship();

    void update_position();
    
    void draw();
    void load_ship_graphics();

    void on_key_press(unsigned char key, int x, int y);
    void on_key_release(unsigned char key, int x, int y);
};
