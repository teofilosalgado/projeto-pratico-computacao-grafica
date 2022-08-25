#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include "shader.h"
#include "texture.h"
#include "model.h"


constexpr int WINDOW_WIDTH = 720;
constexpr int WINDOW_HEIGHT = 480;

int main(void) {
	GLFWwindow* window;

	// Inicializa a biblioteca GLFW
	if (!glfwInit())
		return -1;

	// Configura versão mínima do OpenGL e sampling de MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Cria uma nova janela
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Define o contexto da janela
	glfwMakeContextCurrent(window);

	// Inicializa a biblioteca GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	// Define o método de leitura das teclas
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Esconde o cursor do mouse e libera o movimento completo
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Define a cor de fundo como azul escuro
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Centraliza o cursor do mouse
	glfwPollEvents();
	glfwSetCursorPos(window, static_cast<float>(WINDOW_WIDTH) / 2.0f, static_cast<float>(WINDOW_HEIGHT) / 2.0f);

	// Ativa e configura o depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Ativa o culling
	glEnable(GL_CULL_FACE);

	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\cube.vert", "shaders\\cube.frag");
	GLuint programID = shader->program_id;

	// Carrega a textura
	Texture* texture = new Texture("assets\\textures\\cube.png");

	// Obtém um handle para a uniforme "myTextureSampler"
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler"); 


	// Monta a matrix de projeção
	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Lê o modelo
	Model* model = new Model("assets\\models", "cube.obj");

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, model->vertices.size() * sizeof(glm::vec3), &model->vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, model->uvs.size() * sizeof(glm::vec2), &model->uvs[0], GL_STATIC_DRAW);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Enquanto o usuário não fechar a janela:
	while (!glfwWindowShouldClose(window)) {
		// Limpa a tela
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->texture_id);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Troca os buffers
		glfwSwapBuffers(window);

		// Aguarda até que eventos ocorram
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}