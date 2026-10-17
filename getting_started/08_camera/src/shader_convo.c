#include "shader_convo.h"

void activate_shader(unsigned int shader_program_id){
	glUseProgram(shader_program_id);
}

void set_uniform_int(unsigned int shader_program_id, char* uniform_name, int value) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform1i(uniform_location, value);

}
void set_uniform_int_2(unsigned int shader_program_id, char* uniform_name, int value1, int value2) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform2f(uniform_location, value1, value2);

}
void set_uniform_int_3(unsigned int shader_program_id, char* uniform_name, int value1, int value2, int value3) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform3f(uniform_location, value1, value2, value3);

}

void set_uniform_int_4(unsigned int shader_program_id, char* uniform_name, int value1, int value2, int value3, int value4) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform4f(uniform_location, value1, value2, value3, value4);

}

void set_uniform_float(unsigned int shader_program_id, char* uniform_name, float value) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform1f(uniform_location, value);

}
void set_uniform_float_2(unsigned int shader_program_id, char* uniform_name, float value1, float value2) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform2f(uniform_location, value1, value2);

}
void set_uniform_float_3(unsigned int shader_program_id, char* uniform_name, float value1, float value2, float value3) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform3f(uniform_location, value1, value2, value3);

}

void set_uniform_float_4(unsigned int shader_program_id, char* uniform_name, float value1, float value2, float value3, float value4) {

	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniform4f(uniform_location, value1, value2, value3, value4);

}

void set_uniform_mat4(unsigned int shader_program_id, char* uniform_name, mat4s matrix){
	glUseProgram(shader_program_id);
	unsigned int uniform_location = glGetUniformLocation(shader_program_id, uniform_name);
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (float*)matrix.raw); 

}


