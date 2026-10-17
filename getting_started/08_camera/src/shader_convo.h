#ifndef SHADER_CONVO_H
#define SHADER_CONVO_H
#include <glad/glad.h>
#include <cglm/struct.h>

void activate_shader(unsigned int shader_program_id);
void set_uniform_int(unsigned int shader_program_id, char* uniform_name, int value);
void set_uniform_int_2(unsigned int shader_program_id, char* uniform_name, int value1, int value2);
void set_uniform_int_3(unsigned int shader_program_id, char* uniform_name, int value1, int value2, int value3);
void set_uniform_int_4(unsigned int shader_program_id, char* uniform_name, int value1, int value2, int value3, int value4);
void set_uniform_float(unsigned int shader_program_id, char* uniform_name, float value);
void set_uniform_float_2(unsigned int shader_program_id, char* uniform_name, float value1, float value2);
void set_uniform_float_3(unsigned int shader_program_id, char* uniform_name, float value1, float value2, float value3);
void set_uniform_float_4(unsigned int shader_program_id, char* uniform_name, float value1, float value2, float value3, float value4);

void set_uniform_mat4(unsigned int shader_program_id, char* uniform_name, mat4s matrix);
#endif
