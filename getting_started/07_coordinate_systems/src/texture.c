#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void init_stb() {
	stbi_set_flip_vertically_on_load_thread(1);
}

unsigned int init_texture(char* texture_image_file,  GLenum image_type, GLenum texture_unit, GLenum texture_wrap) {

	// Load image into memory using stb_image library.
	int width, height, nr_channels;
	unsigned char* data = stbi_load(texture_image_file, &width, &height, &nr_channels, 0);
	if(!data) {
		printf("ERROR: Failed to load image data\n");
		return 1;
	}

	// Generate a texture object ID with which we'll operate with when this particular texture
	// will be in question
	unsigned int texture;
	glGenTextures(1, &texture);

	// activate the texture unit 0. With this we can activate multiple textures and use them in the
	// shader (eg. normal map textures)
	// in most graphics drivers texture unit 0 is activated by default, this stands here as "good practice"
	// and to demonstrate this is possible
	glActiveTexture(texture_unit);
	// We BIND the texture ID to GL_TEXTURE_2D so any further "actions" that operate on GL_TEXTURE_2D will be operated on the binded texture.
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture wrapping mode. You have to set it up for each axis of the texture
	// s -> x axis
	// t -> y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, image_type, GL_UNSIGNED_BYTE, data);


	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return texture;
}
