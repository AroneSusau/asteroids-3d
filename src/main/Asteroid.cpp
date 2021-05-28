#include "../headers/Asteroid.h"

Asteroid::Asteroid(GLuint texture, Vector3* v)
{
  body          = new RigidBody();
  velocity      = v;
  rotation      = new Vector3();

  float rand    = ((float) V3_Math::random(1, 100)) / 100;

  size          = 500 + 2000 * rand;
  health        = 100 + size/10;
  max_health    = health;
  points        = size * 2;

  this->texture = texture;

  vertices      = new std::vector<std::vector<Vector3*>*>();
  normals       = new std::vector<std::vector<Vector3*>*>();
  textcoords    = new std::vector<std::vector<Vector3*>*>();

  entered_arena = false;
  destroyed     = false;

  init();
  init_rotation();
}

Asteroid::~Asteroid()
{
  delete body;
  delete velocity;
  delete rotation;

  for (size_t i = 0; i < vertices->size(); ++i)
  {
    for (size_t j = 0; j < vertices->size(); ++j)
    {
      delete vertices->at(i)->at(j);
      delete normals->at(i)->at(j);
      delete textcoords->at(i)->at(j);
    }

      delete vertices->at(i);
      delete normals->at(i);
      delete textcoords->at(i);
  }

  delete vertices;
  delete normals;
  delete textcoords;
}

void Asteroid::init()
{
  float radius      = size;
  float sectorCount = ASTEROID_DIVISIONS;
  float stackCount  = ASTEROID_DIVISIONS;

  float x, y, z, xy;
  float nx, ny, nz, lengthInv = 1.0f / radius;
  float s, t; 

  float sectorStep = 2 * M_PI / sectorCount;
  float stackStep = M_PI / stackCount;
  float sectorAngle, stackAngle;

  for(int i = 0; i <= stackCount; ++i)
  {
      float rand = ((float) V3_Math::random(55, 100)) / 100;
      rand = V3_Math::random(1, 100) % 7 == 0 ? 1 : rand;

      stackAngle = M_PI / 2 - i * stackStep;
      xy = radius * cosf(stackAngle);
      z = radius * sinf(stackAngle) * rand;

      vertices->push_back(new std::vector<Vector3*>());
      normals->push_back(new std::vector<Vector3*>());
      textcoords->push_back(new std::vector<Vector3*>());

      for(int j = 0; j <= sectorCount; ++j)
      {

        float rand2 = ((float) V3_Math::random(55, 100)) / 100;
        rand2 = V3_Math::random(1, 100) % 7 == 0 ? 1 : rand2;
        
        sectorAngle = j * sectorStep;

        x = xy * cosf(sectorAngle);
        y = xy * sinf(sectorAngle) * rand2;
        
        vertices->at(i)->push_back(new Vector3(x, y, z));

        nx = x * lengthInv;
        ny = y * lengthInv;
        nz = z * lengthInv;
        
        normals->at(i)->push_back(new Vector3(nx, ny, nz));

        s = ((float) j / sectorCount);
        t = ((float) i / stackCount);

        textcoords->at(i)->push_back(new Vector3(s, t, 0));
      }
  }
}

void Asteroid::init_rotation()
{
  int xr = V3_Math::random(1, 2) == 1 ? -100 : 100;
  int yr = V3_Math::random(1, 2) == 1 ? -100 : 100;
  int zr = V3_Math::random(1, 2) == 1 ? -100 : 100;
  
  int value = V3_Math::random(1, 3);
  
  xr = value == 1 ? xr : 0;
  yr = value == 2 ? yr : 0;
  zr = value == 3 ? zr : 0;

  rotation->x = xr;
  rotation->y = yr;
  rotation->z = zr;
}

void Asteroid::draw()
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPushMatrix();
  glTranslatef(body->position->x, body->position->y, body->position->z - 100);
  
  glPushMatrix();

    float mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    float matrix [] = {
      body->right->x,    body->right->y,    body->right->z,    0.0f,              
      body->up->x,       body->up->y,       body->up->z,      0.0f,
      body->forward->x,  body->forward->y,  body->forward->z, 0.0f,
      0, 0, 0, 1.0f
    };

    glMultMatrixf(matrix);
    draw_health_bar();
  
  glRotatef(body->orientation->x, 1, 0, 0);
  glRotatef(body->orientation->y, 0, 1, 0);
  glRotatef(body->orientation->z, 0, 0, 1);

  Materials::asteroid();

  glBindTexture(GL_TEXTURE_2D, texture);

  Vector3* v1, *v2, *t1, *t2, *n1, *n2; 

  for (int i = 0; i <= ASTEROID_DIVISIONS - 1; i++) 
  {
    glBegin(GL_TRIANGLE_STRIP);
    
    for (int j = 0; j <= ASTEROID_DIVISIONS; j++)
    {
      v1 = vertices->at(i)->at(j);
      t1 = textcoords->at(i)->at(j);
      n1 = normals->at(i)->at(j);

      glNormal3f(n1->x, n1->y, n1->z);
      glTexCoord2f(t1->x, t1->y);
      glVertex3f(v1->x, v1->y, v1->z);

      v2 = vertices->at(i + 1)->at(j);
      t2 = textcoords->at(i + 1)->at(j);
      n2 = normals->at(i + 1)->at(j);

      glNormal3f(n2->x, n2->y, n2->z);
      glTexCoord2f(t2->x, t2->y);
      glVertex3f(v2->x, v2->y, v2->z);
    }

    glEnd();
  }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void Asteroid::has_entered_arena()
{
  entered_arena = (
    (body->position->x >= -WALL_TOTAL_DIST && body->position->x <= WALL_TOTAL_DIST) &&
    (body->position->y >= -WALL_TOTAL_DIST && body->position->y <= WALL_TOTAL_DIST) &&
    (body->position->z >= -WALL_TOTAL_DIST && body->position->z <= WALL_TOTAL_DIST)
  );
}

bool Asteroid::has_collided(RigidBody* o_body) 
{
  float dist = V3_Math::magnitude(V3_Math::subtract(body->position, o_body->position));
  bool result = false;
  
  if (dist < size)
  {
    hit(20);
    result = true;
  }

  return result;
}

void Asteroid::hit(float amount) 
{
  health -= amount;

  if (health <= 0)
  {
    destroyed = true;
  }
}

void Asteroid::draw_health_bar()
{
  glBegin(GL_QUADS);
      glVertex3d(-size, 200 + size, 0);
      glVertex3d(size,  200 + size, 0);
      glVertex3d(size,  200 + size + 300, 0);
      glVertex3d(-size, 200 + size + 300, 0);
    glEnd();

    glEnable(GL_LIGHTING);

    Materials::emerald();

    float h = health / max_health;

    glBegin(GL_QUADS);
      glVertex3d(-size + 100, 300 + size, -10);
      glVertex3d((size - 100) * h,  300 + size, -10);
      glVertex3d((size - 100) * h,  300 + size + 100, -10);
      glVertex3d(-size + 100, 300 + size + 100, -10);
    glEnd();

  glPopMatrix();

}