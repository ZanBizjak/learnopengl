#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <glad/glad.h>

struct ShaderInfo {
	// String of source_code for the shader.
	const char* source_code;

	// Define the type of shader (vertex/fragment)
	GLenum shader_type;

};

unsigned int compile_and_link_shader_program(struct ShaderInfo shader_info[], int shader_info_size);
unsigned int create_shader_program(unsigned int shader_ids[], int num_of_shaders);
unsigned int compile_shader(const char* shaderSourceCode, GLenum shaderType,const char* file_name);


#endif
