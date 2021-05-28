#include "../headers/Skybox.h"

Skybox::Skybox()
{
  filenames[0] = "assets/skybox/front.png";
  filenames[1] = "assets/skybox/back.png";
  filenames[2] = "assets/skybox/left.png";
  filenames[3] = "assets/skybox/right.png";
  filenames[4] = "assets/skybox/top.png";
  filenames[5] = "assets/skybox/bot.png";
}

Skybox::~Skybox()
{}

void Skybox::draw()
{
  if (ENABLE_SKYBOX)
  {
    float scale = 4.0f;
    float mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float mat_shininess[] = { 100.0 };

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    
    glPushMatrix();
    
    glTranslatef(world->camera->body->position->x, world->camera->body->position->y, world->camera->body->position->z);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    
    glTexCoord2f(0, 0);
    glVertex3f(-scale, -scale, scale);

    glTexCoord2f(1, 0);
    glVertex3f(scale, -scale, scale);

    glTexCoord2f(1, 1);
    glVertex3f(scale, scale, scale);

    glTexCoord2f(0, 1);
    glVertex3f(-scale, scale, scale);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-scale, -scale, -scale);

    glTexCoord2f(0, 0);
    glVertex3f(scale, -scale, -scale);

    glTexCoord2f(0, 1);
    glVertex3f(scale, scale, -scale);

    glTexCoord2f(1, 1);
    glVertex3f(-scale, scale, -scale);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[2]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    
    glTexCoord2f(0, 0);
    glVertex3f(-scale, -scale, -scale);

    glTexCoord2f(0, 1);
    glVertex3f(-scale, scale, -scale);

    glTexCoord2f(1, 1);
    glVertex3f(-scale, scale, scale);

    glTexCoord2f(1, 0);
    glVertex3f(-scale, -scale, scale);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[3]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    
    glTexCoord2f(1, 0);
    glVertex3f(scale, -scale, -scale);

    glTexCoord2f(1, 1);
    glVertex3f(scale, scale, -scale);

    glTexCoord2f(0, 1);
    glVertex3f(scale, scale, scale);
    
    glTexCoord2f(0, 0);
    glVertex3f(scale, -scale, scale);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[4]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-scale, -scale, -scale);

    glTexCoord2f(1, 0);
    glVertex3f(scale, -scale, -scale);

    glTexCoord2f(1, 1);
    glVertex3f(scale, -scale, scale);

    glTexCoord2f(0, 1);
    glVertex3f(-scale, -scale, scale);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[5]);

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    
    glTexCoord2f(0, 1);
    glVertex3f(-scale, scale, -scale);

    glTexCoord2f(1, 1);
    glVertex3f(scale, scale, -scale);
    
    glTexCoord2f(1, 0);
    glVertex3f(scale, scale, scale);

    glTexCoord2f(0, 0);
    glVertex3f(-scale, scale, scale);
    glEnd();

    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
  }
}

void Skybox::load_skybox_textures()
{
  for (int i = 0; i < 6; ++i)
  {
    textures[i] = Util::load_texture(filenames[i].c_str(), false);
  }
}