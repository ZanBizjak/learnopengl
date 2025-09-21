#ifndef TEXTURE_H
#define TEXUTRE_H
#include <glad/glad.h>

void init_stb();
unsigned int init_texture(char* texture_image_file,  GLenum image_type, GLenum texture_unit, GLenum texture_wrap);


#endif
