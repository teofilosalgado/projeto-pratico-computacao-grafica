#version 330 core

// Dados dos v�rtices
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;

// Dados dos v�rtices a serem passados pro shader de fragmentos
out vec3 fragment_position;
out vec2 fragment_uv;
out vec3 fragment_normal;
out vec3 fragment_light_position;

// Uniformes de modelo, vis�o e proje��o
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Uniforme de escala
uniform float scale;

// Uniformes de ilumina��o
uniform vec3 light_position;

void main() {
	// Posi��o resultante do v�rtice obtida da multiplica��o do mvp com a posi��o original
	gl_Position =  projection * view * model * vec4(vertex_position * scale, 1.0);
	
	// Passando dados
	fragment_position = vec3(view * model * vec4(vertex_position, 1.0));
	fragment_uv = vertex_uv;
	fragment_normal = mat3(transpose(inverse(view * model))) * vertex_normal;
	fragment_light_position = vec3(view * vec4(light_position, 1.0));
}