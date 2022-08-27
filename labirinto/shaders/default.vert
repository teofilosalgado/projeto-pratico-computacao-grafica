#version 330 core

// Dados dos v�rtices
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

// Posicionamento de textura resultante
out vec2 uv;

// Uniformes de model, vis�o e proje��o
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// Posi��o resultante do v�rtice obtida da multiplica��o do mvp com a posi��o original
	gl_Position =  projection * view * model * vec4(vertex_position, 1.0);
	
	// Textura resultante do v�rtice, n�o � necess�rio realizar nenhuma opera��o
	uv = vertex_uv;
}