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

#include <vector>
#include <string>
#include <iostream>

typedef struct
{
  std::vector<float> vx;
  std::vector<float> vy;
  std::vector<float> vz;

  std::vector<float> nx;
  std::vector<float> ny;
  std::vector<float> nz;

  std::vector<float> tx;
  std::vector<float> ty;
  
  float size;
  
} model_vertex;

class Util
{
  public:
    
    static void load_model(const char* filename, const char* materialpath, model_vertex& model);
    static GLuint load_texture(const char* filename, bool flip);
    static GLuint load_anim_texture(const char* filename, bool flip);
};