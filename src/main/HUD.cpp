#include "../headers/HUD.h"

HUD::HUD(World* world)
{
  this->world = world;
}

HUD::~HUD()
{}

void HUD::tick()
{
  if (world->game_state == GAME_START)
  {
    start_screen();
  }
  else if (world->game_state == GAME_OVER)
  {
    game_over_screen();
  }
  else if (world->game_state == GAME_PLAYING)
  {
    playing_screen();
  }
}

void  HUD::start_screen() {
  
  float window_width = glutGet(GLUT_WINDOW_WIDTH);
  float window_height = glutGet(GLUT_WINDOW_HEIGHT);

  glDisable(GL_LIGHTING);
  glDisable(GL_FOG);
  glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, window_width, 0.0, window_height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  

  float x1 = (world->viewport_width / 6.0f) * 2.0f;
  float y1 = (world->viewport_height / 6.0f) * 2.0f;

  float x2 = (world->viewport_width / 6.0f) * 4.0f;
  float y2 = (world->viewport_height / 6.0f) * 4.0f;

  glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x2, y1);
    glVertex2d(x2, y2);
    glVertex2d(x1, y2);
  glEnd();

  const unsigned char title [42] = "A    S    T    E    R    O    I    D    S";
  const unsigned char subtitle [36] = "Interactive 3d graphics & animation";
  const unsigned char auth [21] = "Arone Susau s3728977";
  const unsigned char msg [23] = "Press any key to begin";
  
  int title_width = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, title) / 2.0f;
  
  glColor3f(1.0, 1.0, 1.0); 
  glRasterPos2f(window_width/2 - title_width, window_height / 2.0f + 50.0f);

  for (int i = 0; i < std::strlen((char*) title); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
  }

  glRasterPos2f(window_width/2 - title_width, window_height / 2.0f - 10.0f);

  for (int i = 0; i < std::strlen((char*) subtitle); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, subtitle[i]);
  }

  glRasterPos2f(window_width/2 - title_width, window_height / 2.0f - 40.0f);

  for (int i = 0; i < std::strlen((char*) auth); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, auth[i]);
  }

  glRasterPos2f(window_width/2 - title_width, window_height / 2.0f - 90.0f);

  for (int i = 0; i < std::strlen((char*) msg); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, msg[i]);
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glEnable(GL_LIGHTING);
  glEnable(GL_FOG);
}

void HUD::game_over_screen()
{
  
  float window_width = glutGet(GLUT_WINDOW_WIDTH);
  float window_height = glutGet(GLUT_WINDOW_HEIGHT);

  glDisable(GL_LIGHTING);
  glDisable(GL_FOG);
  glDisable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, window_width, 0.0, window_height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  float x1 = (window_width / 6.0f) * 2.0f;
  float y1 = (window_height / 6.0f) * 2.0f;

  float x2 = (window_width / 6.0f) * 4.0f;
  float y2 = (window_height / 6.0f) * 4.0f;

  glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x2, y1);
    glVertex2d(x2, y2);
    glVertex2d(x1, y2);
  glEnd();

  std::string score = "Score: " + std::to_string((int) world->player_points) + " | " + "Time: " + std::to_string((int) world->player_death_time / 60) + ":" + std::to_string((int) world->player_death_time % 60);
  const unsigned char msg_c [28] = "Press any key to continue";
  const unsigned char title [24] = "G A M E  O V E R  M A N";
  const char * subtitle = score.c_str();
  
  int msg_width = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (unsigned char *) msg_c) / 2.0;
  
  glColor3f(1.0, 1.0, 1.0); 
  glRasterPos2f(window_width/2 - msg_width, window_height / 2 + 50);

  for (int i = 0; i < std::strlen((char*) title); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
  }

  glRasterPos2f(window_width/2 - msg_width, window_height / 2 - 50);

  for (int i = 0; i < std::strlen((char*) subtitle); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, subtitle[i]);
  }

  glRasterPos2f(window_width/2 - msg_width, window_height / 2);

  for (int i = 0; i < std::strlen((char*) msg_c); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, msg_c[i]);
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glEnable(GL_LIGHTING);
  glEnable(GL_FOG);
}

void HUD::playing_screen()
{
  glDisable(GL_LIGHTING);
  glDisable(GL_FOG);
  glDisable(GL_TEXTURE_2D);
  glPushAttrib(GL_CURRENT_BIT);

  float window_width = glutGet(GLUT_WINDOW_WIDTH);
  float window_height = glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, window_width, 0.0, window_height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  std::string score = "Score: " + std::to_string((int) world->player_points) + " - Next Wave: " + std::to_string((int) world->asteroid_generator->next_spawn % 60);
  std::string time = "Time: " + std::to_string((int) world->time->now / 60) + ":" + std::to_string((int) world->time->now % 60);

  glColor3f(1.0, 3.0, 0.0); 
  glRasterPos2f(25, window_height - 40);

  for (int i = 0; i < score.length(); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);
  }

  glRasterPos2f(window_width - 110, window_height - 40);

  for (int i = 0; i < time.length(); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, time[i]);
  }

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glPopAttrib();
  glEnable(GL_LIGHTING);
  glEnable(GL_FOG);
}
