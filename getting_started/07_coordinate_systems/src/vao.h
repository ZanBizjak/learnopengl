#ifndef VAO_H
#define VAO_H
#include <glad/glad.h>

// Custom struct for representing how the vertex attributes are layed out 
// in the vertecies array
//
// Each vertex, besides it's location on the screen can also hold additional information about it, 
// such as color and the texture coordinates that decide how to sample te texture onto the drawn object.
// This makes it so that we have to tell OpenGL *how* the array is structured. This "telling" is done
// via calculating the offsets for each of these attributes per single veretx.
struct VertexAttribInfo {
  // Number of attributes that a vertex holds. If only positional attributes would be held in the array (such as {0.0, 1.0, 2.0}),
  // then number of attributes is 1. If besides it a texture coordinate is passed ( the array is now {0.0, 1.0, 2.0, 0.0, 0.5})
  // we say the number of attributes is 2                                                             ^positional    ^texture coords
  int num_of_attribs;

  // Array describing how many numbers each attribute holds. In the above example it can be seen that positional attribute has 3 values
  // while the texture coordinate value has 2 values. in this case the array of attrib_lengths would look like {3, 2}
  int* attrib_lengths;

  // result of sizeof({type}), where {type} is the type of the array where the vertex data is held in. The above arrays, holding
  // vertex data are floats, so this value would hold sizeof(float) value.
  int size_of_array_type;
};


unsigned int init_vao(float vertices[], int vertices_size, unsigned int indices[], int indices_size, struct VertexAttribInfo vertexAttribInfo); 
void update_vertices_in_buff(unsigned int VAO, float vertices[],unsigned int vertices_size_bytes);
struct VertexAttribInfo construct_vertex_attrib_info(int num_of_attribs, int* attrib_lengths, int sizeof_array_type);

#endif
