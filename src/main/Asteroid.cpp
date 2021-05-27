#include "../headers/Asteroid.h"

Asteroid::Asteroid()
{
  body     = new RigidBody();
  velocity = new Vector3();

  vertices   = new std::vector<std::vector<Vector3*>*>();
  normals    = new std::vector<std::vector<Vector3*>*>();
  textcoords = new std::vector<std::vector<Vector3*>*>();

  init();
}

Asteroid::~Asteroid()
{
  delete body;
  delete velocity;

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

  float radius      = 1;
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
      stackAngle = M_PI / 2 - i * stackStep;
      xy = radius * cosf(stackAngle);
      z = radius * sinf(stackAngle);

      vertices->push_back(new std::vector<Vector3*>());
      normals->push_back(new std::vector<Vector3*>());
      textcoords->push_back(new std::vector<Vector3*>());

      for(int j = 0; j <= sectorCount; ++j)
      {
          sectorAngle = j * sectorStep;

          x = xy * cosf(sectorAngle);
          y = xy * sinf(sectorAngle);
          
          vertices->at(i)->push_back(new Vector3(x, y, z));

          nx = x * lengthInv;
          ny = y * lengthInv;
          nz = z * lengthInv;
          
          normals->at(i)->push_back(new Vector3(nx, ny, nz));

          s = (float) j / sectorCount;
          t = (float) i / stackCount;

          textcoords->at(i)->push_back(new Vector3(s, t, 0));
      }
  }
}

void Asteroid::draw()
{
  
  glEnable(GL_LIGHTING);
  glPushMatrix();
  glTranslatef(body->position->x, body->position->y, body->position->z - 100);
  glScalef(10, 10, 10);

  Vector3* v1, *v2, *n1, *n2; 
  int row1, row2;

  for (int i = 0; i <= ASTEROID_DIVISIONS - 1; i++) 
  {
    glBegin(GL_TRIANGLE_STRIP);

    Materials::brass();
      
    for (int j = 0; j <= ASTEROID_DIVISIONS; j++)
    {
      v1 = vertices->at(i)->at(j);
      n1 = normals->at(i)->at(j);

      glNormal3f(n1->x, n1->y, n1->z);
      glVertex3f(v1->x, v1->y, v1->z);

      v2 = vertices->at(i + 1)->at(j);
      n2 = normals->at(i + 1)->at(j);

      glNormal3f(n2->x, n2->y, n2->z);
      glVertex3f(v2->x, v2->y, v2->z);
    }

    glEnd();
  }
  glPopMatrix();
}