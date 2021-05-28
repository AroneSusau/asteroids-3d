#include "../headers/Util.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "./../headers/tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb_image.h"

void Util::load_model(const char* filename, const char* materialpath, model_vertex& model)
{
  std::string inputfile = filename;
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = materialpath;

  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
        std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  auto& attrib = reader.GetAttrib();
  auto& shapes = reader.GetShapes();
  // auto& materials = reader.GetMaterials();

  for (size_t s = 0; s < shapes.size(); s++) {  
    
    size_t index_offset = 0;
    
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      
      size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

      for (size_t v = 0; v < fv; v++) {

        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
        tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
        tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

        model.vx.push_back(vx);
        model.vy.push_back(vy);
        model.vz.push_back(vz);
  
        if (idx.normal_index >= 0) {
          tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
          tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
          tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

          model.nx.push_back(nx);
          model.ny.push_back(ny);
          model.nz.push_back(nz);
        }

        if (idx.texcoord_index >= 0) {
          tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
          tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

          model.tx.push_back(tx);
          model.ty.push_back(ty);
        }
      }

      index_offset += fv;
      shapes[s].mesh.material_ids[f];

      model.size = model.vx.size();
    }
  }
}

GLuint Util::load_texture(const char* filename, bool flip) {
  int width, height, components;
  unsigned char *data; 
  GLuint id;

  stbi_set_flip_vertically_on_load(flip);

  data = stbi_load(filename, &width, &height, &components, STBI_rgb);
  glPushAttrib(GL_TEXTURE_BIT);
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
  free(data);
  glPopAttrib();

  return id;
}

GLuint Util::load_anim_texture(const char* filename, bool flip) {
  int width, height, components;
  unsigned char *data; 
  GLuint id;

  stbi_set_flip_vertically_on_load(flip);

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
