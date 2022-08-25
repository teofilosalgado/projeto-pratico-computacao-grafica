#version 330 core

// Dados dos vértices
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

// Posicionamento de textura resultante
out vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

void main() {
	// Posição resultante do vértice obtida da multiplicação do mvp com a posição original
	gl_Position =  mvp * vec4(vertex_position,1);
	
	// Textura resultante do vértice, não é necessário realizar nenhuma operação
	uv = vertex_uv;
}