#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>

#include <stdio.h>

#include "shader_loader.h"
#include "shader_convo.h"
#include "vao.h"
#include "texture.h"



GLFWwindow* init_graphics();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

const char* vertexShaderSource = "vertex.vert";
const char* fragmentShaderSource = "fragment.frag";

float texture_ratio = 0.8f;


int main() {
	GLFWwindow* window = init_graphics();
	if(window == NULL) {
		return 1;
	}
	init_stb();


	// Shader setup with custom ShaderInfo struct
	struct ShaderInfo vertexShaderInfo;
	vertexShaderInfo.shader_type = GL_VERTEX_SHADER;
	vertexShaderInfo.source_code = vertexShaderSource;

	struct ShaderInfo fragmentShaderOrangeInfo;
	fragmentShaderOrangeInfo.shader_type = GL_FRAGMENT_SHADER;
	fragmentShaderOrangeInfo.source_code = fragmentShaderSource;



	// Shader compilation
	// --------------------------------------------
	struct ShaderInfo shader_setup[] = {vertexShaderInfo, fragmentShaderOrangeInfo}; 
	unsigned int shader_program = compile_and_link_shader_program(shader_setup, 2);

	if(!shader_program) {
		return 1;
	}
	//----------------------------------------------------

	// Display vertecies logic
	float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices_square[] = {  // note that we start from 0!
	    0, 1, 2,   // first triangle
	    2, 0, 3,	//second triangle
	};

        struct VertexAttribInfo rect_vertex_info = construct_vertex_attrib_info(3, (int[]){3, 3, 2}, sizeof(float));

	// VAO is the id of the Vertex Array Object
	unsigned int VAO_rect = init_vao(vertices, sizeof(vertices), indices_square, sizeof(indices_square), rect_vertex_info);
	
	if(!VAO_rect) {
		printf("Couldn't init vao!\n");

		return 1;
	}


	// Texture setup
	//-------------------------------------------
	// Set texture filtering mode. There are settings for either when texture is scaled down(MIN) or up(MAG)
	// You have to set both
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	unsigned int texture_container = init_texture("container.jpg", GL_RGB, GL_TEXTURE0, GL_CLAMP_TO_EDGE);
	unsigned int texture_awesomeface = init_texture("trololo.png", GL_RGBA, GL_TEXTURE1, GL_REPEAT);

	set_uniform_int(shader_program, "container", 0);
	set_uniform_int(shader_program, "awesomeface", 1);

	//-------------------------------------------
	//
	




	// rendering loop
	while(!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Use this shader program for rendering vertecies to the screen
		//
		glUseProgram(shader_program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_container);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_awesomeface);
		glBindVertexArray(VAO_rect);

		set_uniform_float(shader_program, "textureRatio", texture_ratio);

		// Transformations
		// ------------------------------------------
		mat4s trans_rotate = GLMS_MAT4_IDENTITY_INIT;
		trans_rotate = glms_translate(trans_rotate, (vec3s){0.5f, -0.5f, 0.0f});
		trans_rotate = glms_rotate(trans_rotate, (float)glfwGetTime(), (vec3s){0.0f, 0.0f, 1.0f});
		set_uniform_mat4(shader_program, "transform", trans_rotate);

		glDrawElements(GL_TRIANGLES, sizeof(indices_square) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		mat4s trans_scale = GLMS_MAT4_IDENTITY_INIT;
		trans_scale = glms_translate(trans_scale, (vec3s){-0.5f, 0.5f, 0.0f});
		float time = (float)glfwGetTime();
		trans_scale = glms_scale(trans_scale, (vec3s){(float)sin(time), (float)sin(time), 1.0f});
		set_uniform_mat4(shader_program, "transform", trans_scale);
		glDrawElements(GL_TRIANGLES, sizeof(indices_square) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// check and call events and swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

GLFWwindow* init_graphics() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
	if(window == NULL) {

		printf("ERROR: Failed to create GLFW window\n");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("ERROR: Failed to initialize GLAD\n");
		return NULL;
	}

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		texture_ratio += 0.001f;
	}

	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		texture_ratio -= 0.001f;
	}
}

