#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

struct ShaderInfo {
	const char* source_code;
	GLenum shader_type;

};


unsigned int compile_and_link_shader_program(struct ShaderInfo shader_info[], int shader_info_size);
unsigned int create_shader_program(unsigned int shader_ids[], int num_of_shaders);
void assign_VAO_for_vertices(float vertices[], unsigned int vertices_size, unsigned int ebo_indices[]);
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

const char* fragmentShaderSourceYellow = "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main() {\n"
				"	FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
				"}\0";


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

	struct ShaderInfo fragmentShaderYellowInfo;
	fragmentShaderYellowInfo.shader_type = GL_FRAGMENT_SHADER;
	fragmentShaderYellowInfo.source_code = fragmentShaderSourceYellow;


	// Shader compilation
	// --------------------------------------------
	struct ShaderInfo orange_shader_setup[] = {vertexShaderInfo, fragmentShaderOrangeInfo}; 
	struct ShaderInfo yellow_shader_setup[] = {vertexShaderInfo, fragmentShaderYellowInfo}; 
	unsigned int shader_program_orange = compile_and_link_shader_program(orange_shader_setup, 2);
	if(!shader_program_orange) {
		return 1;
	}
	unsigned int shader_program_yellow = compile_and_link_shader_program(yellow_shader_setup, 2);
	if(!shader_program_yellow) {
		return 1;
	}

	//----------------------------------------------------

	// Display vertecies logic
	float vertices[] = {
		-1.0f, 0.0f, 0.0f,
		-0.5f, 0.8f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.8f, 0.0f,
		 1.0f, 0.0f, 0.0f,
	};
	unsigned int indices_first_triangle[] = {  // note that we start from 0!
	    0, 1, 2,   // first triangle
	};
	unsigned int indices_second_triangle[] = {  // note that we start from 0!
	    2, 3, 4    // second triangle
	};



	// VAO is the id of the Vertex Array Object
	unsigned int VAO_first_triangle;
	glGenVertexArrays(1, &VAO_first_triangle);
	glBindVertexArray(VAO_first_triangle);
	assign_VAO_for_vertices(vertices, sizeof(vertices), indices_first_triangle);
	glBindVertexArray(0);

	unsigned int VAO_second_triangle;
	glGenVertexArrays(1, &VAO_second_triangle);
	glBindVertexArray(VAO_second_triangle);
	assign_VAO_for_vertices(vertices, sizeof(vertices), indices_second_triangle);
	glBindVertexArray(0);


	// rendering loop
	while(!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Use this shader program for rendering vertecies to the screen
		glUseProgram(shader_program_yellow);
		glBindVertexArray(VAO_first_triangle);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(shader_program_orange);
		glBindVertexArray(VAO_second_triangle);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// check and call events and swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}

unsigned int compile_and_link_shader_program(struct ShaderInfo shader_info[], int shader_info_size) {
	unsigned int shader_program_id;
	unsigned int compiled_shaders[shader_info_size];
	for(int i = 0; i < shader_info_size; i++) {
		compiled_shaders[i] = compile_shader(shader_info[i].source_code, shader_info[i].shader_type);
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

void assign_VAO_for_vertices(float vertices[], unsigned int vertices_size_bytes, unsigned int ebo_indices[] ) {
	unsigned int VBO;
	unsigned int EBO;

	// We generate the buffers
	// VBO is the vertex buffer object ID
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// We bind the VBO id to the GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// We insert our vertecies into the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices_size_bytes, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices_size_bytes, ebo_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		printf("Failed to compile shader. Recieved logs: \n");
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
