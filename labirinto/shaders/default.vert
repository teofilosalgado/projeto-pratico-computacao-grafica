#version 330 core

// Dados dos v�rtices
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

// Posicionamento de textura resultante
out vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

void main() {
	// Posi��o resultante do v�rtice obtida da multiplica��o do mvp com a posi��o original
	gl_Position =  mvp * vec4(vertex_position,1);
	
	// Textura resultante do v�rtice, n�o � necess�rio realizar nenhuma opera��o
	uv = vertex_uv;
}