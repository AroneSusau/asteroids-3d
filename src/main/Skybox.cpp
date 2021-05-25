#include "../headers/Skybox.h"

Skybox::Skybox()
{
  filenames[0] = "skybox/front.png";
  filenames[1] = "skybox/back.png";
  filenames[2] = "skybox/left.png";
  filenames[3] = "skybox/right.png";
  filenames[4] = "skybox/top.png";
  filenames[5] = "skybox/bot.png";
}

Skybox::~Skybox()
{}

void Skybox::draw()
{
  float mat_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
  float mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  float mat_shininess[] = { 100.0 };

  glEnable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0, 0);
  glVertex3f(world->camera->body->position->x - 1, world->camera->body->position->y - 1, world->camera->body->position->z - 1);

  glTexCoord2f(1, 0);
  glVertex3f(world->camera->body->position->x + 1, world->camera->body->position->y - 1, world->camera->body->position->z - 1);

  glTexCoord2f(1, 1);
  glVertex3f(world->camera->body->position->x + 1, world->camera->body->position->y + 1, world->camera->body->position->z - 1);

  glTexCoord2f(0, 1);
  glVertex3f(world->camera->body->position->x - 1, world->camera->body->position->y + 1, world->camera->body->position->z - 1);
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
}

void Skybox::load_skybox_textures()
{
  for (int i = 0; i < 6; ++i)
  {
    textures[i] = Util::load_texture(filenames[i].c_str());
  }
}