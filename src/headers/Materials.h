#pragma once

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

class Materials
{
  public:

    static void ship()
    {
      float mat_ambient [] = { 0.8, 0.8, 0.8, 1.0 };
      float mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
      float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
      float mat_shininess[] = { 100.0 };

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    
    }

    static void brass()
    { 
      float mat_ambien1 [] = { 0.1745f, 0.0f, 0.11175f, 0.55f };
      float mat_diffuse1 [] ={ 0.714f, 0.4284f, 0.18144f, 1.0f };
      float mat_specular1 [] = {0.727811f, 0.626959f, 0.626959f, 0.55f };
      float shine = 76.8f ;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambien1);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
      glMaterialf(GL_FRONT, GL_SHININESS, shine);
    }

    static void emerald()
    { 
      float mat_ambient [] ={ 0.0215f, 0.1745f, 0.0215f, 0.55f };
      float mat_diffuse [] ={0.07568f, 0.61424f, 0.07568f, 0.55f };
      float mat_specular [] ={0.633f, 0.727811f, 0.633f, 0.55f };
      float shine = 76.8f;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS, shine);
    }

    static void jade()
    {
      float mat_ambient [] = { 0.135f, 0.2225f, 0.1575f, 0.95f };
      float mat_diffuse [] = {0.54f, 0.89f, 0.63f, 0.95f };
      float mat_specular [] = {0.316228f, 0.316228f, 0.316228f, 0.95f };
      float shine1 = 12.8f;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS, shine1);
    }

    static void asteroid()
    {
      float mat_ambient [] = { 0.25f, 0.20725f, 0.20725f, 1.0f };
      float mat_diffuse [] = { 1.0f, 0.829f, 0.829f, 1.0f };
      float mat_specular [] = { 0.296648f, 0.296648f, 0.296648f, 1.0f };
      float shine = 11.264f;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS, shine);
    }

    static void wall()
    {
      float mat_ambient [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float mat_diffuse [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float mat_specular [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float shine1 = 100.0f;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS, shine1);
    }

    static void explosion()
    {
      float mat_ambient [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float mat_diffuse [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float mat_specular [] = { 1.0f, 1.0f, 1.0f, 1.0f };
      float shine1 = 100.0f;

      glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialf(GL_FRONT, GL_SHININESS, shine1);
    }

};
