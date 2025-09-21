#include "vao.h"
#include <stdlib.h>

int calculate_offset(int* attrib_lengths, int num_of_offsets);
void assign_VAO_for_vertices(float vertices[], unsigned int vertices_size, unsigned int ebo_indices[], int ebo_indices_size, struct VertexAttribInfo vertexAttribInfo);


struct VertexAttribInfo construct_vertex_attrib_info(int num_of_attribs, int* attrib_lengths, int sizeof_array_type) {
	struct VertexAttribInfo vert_attrib_info;
        vert_attrib_info.num_of_attribs = num_of_attribs;
        vert_attrib_info.size_of_array_type = sizeof_array_type;
        vert_attrib_info.attrib_lengths = malloc(num_of_attribs * sizeof_array_type);
	for(int i = 0; i < num_of_attribs; i++) {
	vert_attrib_info.attrib_lengths[i] = attrib_lengths[i];
	}

	return vert_attrib_info;

}

unsigned int init_vao(float vertices[], int vertices_size_bytes, unsigned int indices[], int indices_size_bytes, struct VertexAttribInfo vertexAttribInfo) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	if(!VAO) {
		return 0;
	}
	glBindVertexArray(VAO);
	assign_VAO_for_vertices(vertices, vertices_size_bytes, indices, indices_size_bytes, vertexAttribInfo);
	glBindVertexArray(0);

	return VAO;
}


void assign_VAO_for_vertices(float vertices[], unsigned int vertices_size_bytes, unsigned int ebo_indices[], int ebo_indices_size_bytes, struct VertexAttribInfo vertexAttribInfo) {
	unsigned int VBO;
	unsigned int EBO;

	// We generate the buffers
	// VBO is the vertex buffer object ID
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_indices_size_bytes, ebo_indices, GL_STATIC_DRAW);
	// We bind the VBO id to the GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// We insert our vertecies into the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices_size_bytes, vertices, GL_STATIC_DRAW);
	int vertex_attrib_len = calculate_offset(vertexAttribInfo.attrib_lengths, vertexAttribInfo.num_of_attribs);
	for(int i = 0; i < vertexAttribInfo.num_of_attribs; i++) {
		glVertexAttribPointer(i,
			       vertexAttribInfo.attrib_lengths[i],
			       GL_FLOAT,
			       GL_FALSE,
			       vertex_attrib_len * vertexAttribInfo.size_of_array_type,
			       (void*) ((long)(calculate_offset(vertexAttribInfo.attrib_lengths, i) * vertexAttribInfo.size_of_array_type)));
	glEnableVertexAttribArray(i);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void update_vertices_in_buff(unsigned int VAO, float vertices[],unsigned int vertices_size_bytes) {
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGetBufferPointerv(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, (void*)&VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size_bytes, vertices, GL_DYNAMIC_DRAW);
}

int calculate_offset(int* attrib_lengths, int num_of_offsets) {
	int sum = 0;
	for(int i = 0; i < num_of_offsets; i++) {
		sum += attrib_lengths[i];
	}

	return sum;
}
