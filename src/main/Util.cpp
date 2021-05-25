#include "../headers/Util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

GLuint Util::load_texture(const char* filename) {
  int width, height, components;
  unsigned char *data; 
  GLuint id;

  data = stbi_load(filename, &width, &height, &components, STBI_rgb);
  glPushAttrib(GL_TEXTURE_BIT);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  free(data);
  glPopAttrib();

  return id;
}