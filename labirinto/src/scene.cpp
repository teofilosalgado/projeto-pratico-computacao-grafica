#include "scene.h"

constexpr auto BUFFER_SIZE = 100000;

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

	// Obtém um handle para a uniforme scale no shader de vértice responsável pela escala
	this->scale_uniform = glGetUniformLocation(this->shader->program_id, "scale");

	// Obtém um handle para a uniforme sampler no shader de fragmento responsável pela textura
	this->texture_uniform = glGetUniformLocation(this->shader->program_id, "sampler");

	// Cria o VAO
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// Cria um VBO para os vértices
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Cria um VBO para as texturas (uvs)
	glGenBuffers(1, &uv_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	// Cria um VBO para as normais
	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
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

	// Mapeando o VBO de normais para o VAO
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
	glVertexAttribPointer(
		2,        // Posição do VBO
		3,        // Tamanho
		GL_FLOAT, // Tipo dos elementos
		GL_FALSE, // Normalização
		0,        // Stride
		(void*)0  // Offset
	);
}

void Scene::render(bool is_paused)
{
	// Limpa a tela
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Habilita o shader
	glUseProgram(this->shader->program_id);

	// Define a VP para o shader sob a uniforme de mesmo nome
	glUniformMatrix4fv(this->view_uniform, 1, GL_FALSE, &this->camera->view[0][0]);
	glUniformMatrix4fv(this->projection_uniform, 1, GL_FALSE, &this->camera->projection[0][0]);

	for (Object* object : this->objects)
	{
		// Vincula a textura na unidade de textura 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->texture->texture_id);

		// Envia a textura para o uniforme no shader
		glUniform1i(this->texture_uniform, 0);

		// Envia a escala para o shader sob a uniforme de mesmo nome
		glUniform1f(this->scale_uniform, object->scale);

		// Envia o M para o shader sob a uniforme de mesmo nome
		glUniformMatrix4fv(this->model_uniform, 1, GL_FALSE, &object->position[0][0]);

		// Carrega os vértices dos modelos no buffer dedicado
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, object->model->vertices.size() * sizeof(glm::vec3), object->model->vertices.data());

		// Carrega as texturas (uvs) dos modelos no buffer dedicado
		glBindBuffer(GL_ARRAY_BUFFER, this->uv_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, object->model->uvs.size() * sizeof(glm::vec2), object->model->uvs.data());

		// Carrega as normais dos modelos no buffer dedicado
		glBindBuffer(GL_ARRAY_BUFFER, this->normal_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, object->model->normals.size() * sizeof(glm::vec3), object->model->normals.data());

		// Desenha os vértices da cena
		glDrawArrays(GL_TRIANGLES, 0, object->model->vertices.size());
	}

	// Congela a cena se estiver pausada, impedindo animações
	if (is_paused) {
		return;
	}

	// Animações dos objetos
}
