#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

unsigned int compile_shader(const char* shaderSourceCode, GLenum shaderType);
GLFWwindow* init_graphics();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;
const char* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main() {\n"
				"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main() {\n"
				"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\0";

int main() {
	GLFWwindow* window = init_graphics();
	if(window == NULL) {
		return 1;
	}


	// Shader compilation
	// --------------------------------------------
	unsigned int vertexShader;
	vertexShader = compile_shader(vertexShaderSource, GL_VERTEX_SHADER);
	if(!vertexShader) {
		return 1;
	}

	unsigned int fragmentShader;
	fragmentShader = compile_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	if(!fragmentShader) {
		return 1;
	}

	// ID of the shader program, which serves as the unifying point of which shaders are ran if the
	// given shader program is used for rendering the graphics
	unsigned int shaderProgram;
	// create the ID of the program
	shaderProgram = glCreateProgram();
	//attach vertex and fragment shaders via their IDs to this particular shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Once the shaders are attached and linked in the shader program, we no longer need them in memory.
	// We can delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//----------------------------------------------------

	// Display vertecies logic
	float vertices[] = {
	     0.5f,  0.5f, 0.0f,  // top right
	     0.5f, -0.5f, 0.0f,  // bottom right
	    -0.5f, -0.5f, 0.0f,  // bottom left
	    -0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
	    0, 1, 3,   // first triangle
	    1, 2, 3    // second triangle
	};



	// VAO is the id of the Vertex Array Object
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	// VBO is the vertex buffer object ID
	// We generate the buffer
	// We bind the VBO id to the GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// We insert our vertecies into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	// rendering loop
	while(!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Use this shader program for rendering vertecies to the screen
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// check and call events and swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

unsigned int compile_shader(const char* shaderSourceCode, GLenum shaderType ) {
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
		printf("%s\n",infoLog);
		return -1;
	}
	return shader;
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
