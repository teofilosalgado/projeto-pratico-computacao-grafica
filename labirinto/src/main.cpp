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

	// Define a cor de fundo como preto
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Centraliza o cursor do mouse
	glfwPollEvents();
	glfwSetCursorPos(window, static_cast<float>(WINDOW_WIDTH) / 2.0f, static_cast<float>(WINDOW_HEIGHT) / 2.0f);

	// Ativa e configura o depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Ativa o culling
	glEnable(GL_CULL_FACE);

	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");

	// Carrega a textura
	Texture* texture = new Texture("assets\\textures\\cube.png");

	// Obtém um handle para a uniforme no shader de fragmento responsável pela textura
	GLuint texture_uniform = glGetUniformLocation(shader->program_id, "texture"); 

	// Lê o modelo
	Model* cube = new Model("assets\\models", "cube.obj");

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, cube->vertices.size() * sizeof(glm::vec3), &cube->vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, cube->uvs.size() * sizeof(glm::vec2), &cube->uvs[0], GL_STATIC_DRAW);

	// Obtém um handle para a uniforme no shader de vértice responsável pela matriz mvp
	GLuint mvp_uniform = glGetUniformLocation(shader->program_id, "mvp");

	// Matrix de projeção 
	//   Campode visão: 45° 
	//   Aspecto: WINDOW_WIDTH/WINDOW_HEIGHT
	//   Intervalo de exibição: 0.1 <-> 100
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 1000.0f);

	// Matrix da câmera (visão)
	glm::mat4 view = glm::lookAt(
		glm::vec3(3, 3, 3),   // câmera se encontra em (3, 3, 3) no espaço
		glm::vec3(0, 0, 0),   // olhando para a origem
		glm::vec3(0, 1, 0)    // na orientação correta (cabeça pra cima)
	);
	
	// Matrix do modelo na origem
	glm::mat4 model = glm::mat4(1.0f);

	// Monta a matrix de projeção
	glm::mat4 mvp = projection * view * model;

	// Enquanto o usuário não fechar a janela:
	while (!glfwWindowShouldClose(window)) {
		// Limpa a tela
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Habilita o shader
		glUseProgram(shader->program_id);

		// Envia a mvp para o shader sob a uniforme de mesmo nome
		glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &mvp[0][0]);

		// Vincula a textura na unidade de textura 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->texture_id);

		// Envia a textura para o uniforme no shader
		glUniform1i(texture_uniform, 0);

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

		// Desenha os vértices da cena
		glDrawArrays(GL_TRIANGLES, 0, cube->vertices.size());

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