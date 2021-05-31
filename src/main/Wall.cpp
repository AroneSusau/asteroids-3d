#include "../headers/Wall.h"

Wall::Wall(World* world, float line_count, float line_space, float warning_ratio) {
  
  this->world         = world;
     
  this->line_count    = line_count;
  this->line_space    = line_space;

  this->warning_range = line_count * line_space * warning_ratio;

  this->min_range     = -line_count * line_space + this->warning_range; 
  this->max_range     = line_count * line_space - this->warning_range; 
}

Wall::~Wall() {}

void Wall::wall_distance_warning(Vector3* position)
{
  warnings[0] = position->z > max_range;
  warnings[1] = position->z < min_range;

  warnings[2] = position->x > max_range;
  warnings[3] = position->x < min_range;

  warnings[4] = position->y > max_range;
  warnings[5] = position->y < min_range;
}

void Wall::update_wall_color()
{
  for (int i = 0; i < 6; ++i)
  {
    if (warnings[i])
    {
      colours[i][0] = red[0];
      colours[i][1] = red[1];
      colours[i][2] = red[2];
    }
    else
    {
      colours[i][0] = white[0];
      colours[i][1] = white[1];
      colours[i][2] = white[2];
    }
  }
}

void Wall::draw() 
{
  glPushAttrib(GL_CURRENT_BIT);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  for (int i = -line_count; i <= line_count; ++i)
  {
    // Front
    glColor3f(colours[0][0], colours[0][1], colours[0][2]);
    glVertex3f(i * line_space, -line_space * line_count, line_count * line_space);
    glVertex3f(i * line_space, line_space * line_count, line_count * line_space);

    glVertex3f(-line_space * line_count, i * line_space, line_count * line_space);
    glVertex3f(line_space * line_count, i * line_space, line_count * line_space);

    // back
    glColor3f(colours[1][0], colours[1][1], colours[1][2]);
    glVertex3f(i * line_space, -line_space * line_count, -line_count * line_space);
    glVertex3f(i * line_space, line_space * line_count, -line_count * line_space);

    glVertex3f(-line_space * line_count, i * line_space, -line_count * line_space);
    glVertex3f(line_space * line_count, i * line_space, -line_count * line_space);

    // left
    glColor3f(colours[2][0], colours[2][1], colours[2][2]);
    glVertex3f(line_space * line_count, i * line_space, -line_space * line_count);
    glVertex3f(line_space * line_count, i * line_space, line_space * line_count);

    glVertex3f(line_space * line_count, -line_space * line_count, i * line_space);
    glVertex3f(line_space * line_count, line_space * line_count, i * line_space);

    // right
    glColor3f(colours[3][0], colours[3][1], colours[3][2]);
    glVertex3f(-line_space * line_count, i * line_space, -line_space * line_count);
    glVertex3f(-line_space * line_count, i * line_space, line_space * line_count);

    glVertex3f(-line_space * line_count, -line_space * line_count, i * line_space);
    glVertex3f(-line_space * line_count, line_space * line_count, i * line_space);

    // top
    glColor3f(colours[4][0], colours[4][1], colours[4][2]);
    glVertex3f(i * line_space, line_space * line_count, -line_space * line_count);
    glVertex3f(i * line_space, line_space * line_count, line_space * line_count);

    glVertex3f(-line_space * line_count, line_space * line_count, i * line_space);
    glVertex3f(line_space * line_count, line_space * line_count, i * line_space);

    // bot
    glColor3f(colours[5][0], colours[5][1], colours[5][2]);
    glVertex3f(i * line_space, -line_space * line_count, -line_space * line_count);
    glVertex3f(i * line_space, -line_space * line_count, line_space * line_count);

    glVertex3f(-line_space * line_count, -line_space * line_count, i * line_space);
    glVertex3f(line_space * line_count, -line_space * line_count, i * line_space);
  }
  glEnd();
  glEnable(GL_LIGHTING);
  glPopAttrib();
}

void Wall::wall_ship_collision() 
{
  if (world->game_state == GAME_PLAYING && world->ship->active)
  {
    float dist = WALL_TOTAL_DIST;
  
    bool wall_collision = (
      world->ship->body->position->x > dist || world->ship->body->position->x < -dist ||
      world->ship->body->position->y > dist || world->ship->body->position->y < -dist ||
      world->ship->body->position->z > dist || world->ship->body->position->z < -dist
    );

    if (wall_collision)
    {
      world->game_state = GAME_OVER;
      world->player_death_time = world->time->now;
      world->ship->active = false;
      world->particle_generator->generate_ship_explosion(V3_Math::add(world->ship->body->position, V3_Math::multiply(world->ship->body->forward, 10)), 5);
    }
  }
}
