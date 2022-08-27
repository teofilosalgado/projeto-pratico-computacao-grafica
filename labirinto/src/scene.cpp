#include "scene.h"

constexpr auto BUFFER_SIZE = 10000;

Scene::Scene(Shader* shader, Camera* camera)
{
	// Inicializa as vari�veis
	this->shader = shader;
	this->camera = camera;

	// Inicializa as uniformes
	// Obt�m um handle para cada uniforme no shader de v�rtice respons�vel pela matriz mvp
	this->model_uniform = glGetUniformLocation(this->shader->program_id, "model");
	this->view_uniform = glGetUniformLocation(this->shader->program_id, "view");
	this->projection_uniform = glGetUniformLocation(this->shader->program_id, "projection");

	// Obt�m um handle para a uniforme sampler no shader de fragmento respons�vel pela textura
	this->texture_uniform = glGetUniformLocation(this->shader->program_id, "sampler");

	// Cria o VAO
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// Cria um VBO para os v�rtices
	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Cria um VBO para as texturas (uvs)
	GLuint uv_buffer;
	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Mapeando o VBO de v�rtices para o VAO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(
		0,        // Posi��o do VBO
		3,        // Tamanho
		GL_FLOAT, // Tipo dos elementos
		GL_FALSE, // Normaliza��o
		0,        // Stride
		(void*)0  // Offset
	);

	// Mapeando o VBO de texturas (uvs) para o VAO
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glVertexAttribPointer(
		1,        // Posi��o do VBO
		2,        // Tamanho
		GL_FLOAT, // Tipo dos elementos
		GL_FALSE, // Normaliza��o
		0,        // Stride
		(void*)0  // Offset
	);
}

void Scene::add_object(Object* object)
{
	this->objects.push_back(object);
}
