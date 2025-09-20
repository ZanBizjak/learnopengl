#ifndef VAO_H
#define VAO_H
#include <glad/glad.h>

struct VertexAttribInfo {
  int num_of_attribs;
  int* attrib_lengths;
  int size_of_filetype;
};


unsigned int init_vao(float vertices[], int vertices_size, unsigned int indices[], int indices_size, struct VertexAttribInfo vertexAttribInfo); 

#endif
