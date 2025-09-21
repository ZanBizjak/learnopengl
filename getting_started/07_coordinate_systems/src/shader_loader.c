#include "shader_loader.h"

#include <stdio.h>
#include <stdlib.h>

char* read_file_into_string(const char* file_loc);

unsigned int compile_and_link_shader_program(struct ShaderInfo shader_info[], int shader_info_size) {
	unsigned int shader_program_id;
	unsigned int compiled_shaders[shader_info_size];
	for(int i = 0; i < shader_info_size; i++) {
		char* shader_source_code = read_file_into_string(shader_info[i].source_code);

		compiled_shaders[i] = compile_shader(shader_source_code, shader_info[i].shader_type, shader_info[i].source_code);
		if(!compiled_shaders[i]) {
			return 0;
		}

	}

	// ID of the shader program, which serves as the unifying point of which shaders are ran if the
	// given shader program is used for rendering the graphics
	shader_program_id = create_shader_program(compiled_shaders , sizeof(compiled_shaders) / sizeof(unsigned int));

	// We can delete them
	for(int i = 0; i < shader_info_size; i++) {
		glDeleteShader(compiled_shaders[i]);
	}
	
	return shader_program_id;
}

unsigned int create_shader_program(unsigned int shader_ids[], int num_of_shaders) {
	// ID of the shader program, which serves as the unifying point of which shaders are ran if the
	// given shader program is used for rendering the graphics
	unsigned int shaderProgram;
	// create the ID of the program
	shaderProgram = glCreateProgram();
	//attach vertex and fragment shaders via their IDs to this particular shaderProgram
	//
	for(int i = 0; i < num_of_shaders; i++) {
	glAttachShader(shaderProgram, shader_ids[i]);
	}

	// Link the shader program with all attached shaders.
	glLinkProgram(shaderProgram);
	// Once the shaders are attached and linked in the shader program, we no longer need them in memory.
	// We can delete them

	return shaderProgram;
	
}

unsigned int compile_shader(const char* shaderSourceCode, GLenum shaderType, const char* file_name ) {
	// Shader will be the ID of the vertex shader we'll compile
	unsigned int shader;
	// generate an ID to the shader
	shader = glCreateShader(shaderType);
	// bind the source code that is stored in the shaderSourceCode string onto the shader ID we generated above
	glShaderSource(shader, 1, &shaderSourceCode, NULL);
	// compile the shader by referencig the id that is bound to the source code.
	glCompileShader(shader);

	// check whether the above shader has compiled successfully. The success variable will be non zero if failed.
	// infoLog will get the output log of the vertex compiler. If we fail to compile we would like to know why
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Failed to compile shader %s. Recieved logs: \n", file_name);
		printf("%s\n",infoLog);
		return -1;
	}
	return shader;
}

char* read_file_into_string(const char* file_loc) {

	//this is where we'll read the contents into
	char* file_contents;
	FILE* file_ptr;
	file_ptr = fopen(file_loc, "r");
	if(file_ptr == NULL) {
		printf("ERROR: could not open %s\n", file_loc);
		return 0;
	}
	fseek(file_ptr, 0L, SEEK_END);
	int file_size = ftell(file_ptr);
	file_contents = malloc(file_size + 1);
	rewind(file_ptr);

	int ch = fgetc(file_ptr);
	int ch_loc = 0;
	while(ch != EOF) {
		file_contents[ch_loc] = (char)ch;
		ch_loc++;
		ch = fgetc(file_ptr);
	}
	file_contents[ch] = '\0';

	fclose(file_ptr);

	return file_contents;

}

