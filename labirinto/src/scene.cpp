#include "scene.h"

constexpr auto BUFFER_SIZE = 10000;

Scene::Scene(Shader* shader, Camera* camera)
{
	// Inicializa as variáveis
	this->shader = shader;
	this->camera = camera;

	// Inicializa as uniformes
	// Obtém um handle para cada uniforme no shader de vértice responsável pela matriz mvp
	this->model_uniform = glGetUniformLocation(this->shader->program_id, "model");
	this->view_uniform = glGetUniformLocation(this->shader->program_id, "view");
	this->projection_uniform = glGetUniformLocation(this->shader->program_id, "projection");

	// Obtém um handle para a uniforme sampler no shader de fragmento responsável pela textura
	this->texture_uniform = glGetUniformLocation(this->shader->program_id, "sampler");

	// Cria o VAO
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// Cria um VBO para os vértices
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Cria um VBO para as texturas (uvs)
	GLuint uv_buffer;
	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Mapeando o VBO de vértices para o VAO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(
		0,        // Posição do VBO
		3,        // Tamanho
		GL_FLOAT, // Tipo dos elementos
		GL_FALSE, // Normalização
		0,        // Stride
		(void*)0  // Offset
	);

	// Mapeando o VBO de texturas (uvs) para o VAO
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glVertexAttribPointer(
		1,        // Posição do VBO
		2,        // Tamanho
		GL_FLOAT, // Tipo dos elementos
		GL_FALSE, // Normalização
		0,        // Stride
		(void*)0  // Offset
	);
}

void Scene::add_object(Object* object)
{
	this->objects.push_back(object);
}
