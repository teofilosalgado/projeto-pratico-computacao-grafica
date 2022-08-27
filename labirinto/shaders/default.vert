#version 330 core

// Dados dos vértices
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

// Posicionamento de textura resultante
out vec2 uv;

// Uniformes de model, visão e projeção
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	// Posição resultante do vértice obtida da multiplicação do mvp com a posição original
	gl_Position =  projection * view * model * vec4(vertex_position, 1.0);
	
	// Textura resultante do vértice, não é necessário realizar nenhuma operação
	uv = vertex_uv;
}