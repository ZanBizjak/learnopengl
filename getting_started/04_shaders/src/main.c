#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader_loader.h"
#include "shader_convo.h"
#include "vao.h"

#define TRUE 1
#define FALSE 0


GLFWwindow* init_graphics();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

const char* vertexShaderSource = "vertex.vert";
const char* fragmentShaderSource = "fragment.frag";


int main() {
	GLFWwindow* window = init_graphics();
	if(window == NULL) {
		return 1;
	}

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
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices_first_triangle[] = {  // note that we start from 0!
	    0, 1, 2,   // first triangle
	};
        
        struct VertexAttribInfo triangleVertexInfo;
        triangleVertexInfo.num_of_attribs =2;
        triangleVertexInfo.size_of_filetype = sizeof(float);
        triangleVertexInfo.attrib_lengths = malloc(triangleVertexInfo.num_of_attribs * triangleVertexInfo.size_of_filetype);
	triangleVertexInfo.attrib_lengths[0] = 3;
	triangleVertexInfo.attrib_lengths[1] = 3;



	// VAO is the id of the Vertex Array Object
	unsigned int VAO_first_triangle = init_vao(vertices, sizeof(vertices), indices_first_triangle, sizeof(indices_first_triangle), triangleVertexInfo);
	
	if(!VAO_first_triangle) {
		printf("Couldn't init vao!\n");

		return 1;
	}

	set_float(shader_program, "leftOffset", 0.2);

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
		glBindVertexArray(VAO_first_triangle);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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

		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return NULL;
	}

	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, TRUE);
	}
}
