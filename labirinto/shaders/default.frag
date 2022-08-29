#version 330 core

// Valores do shader de v�rtices
in vec3 fragment_position;
in vec2 fragment_uv;
in vec3 fragment_normal;

// Cor resultante da superf�cie
out vec3 color;

// Constante de unidade de textura
uniform sampler2D sampler;

void main() {
	// A sa�da � definida como a cor na dada posi��o de uv
	color = texture(sampler, fragment_uv, -2.0).rgb;
}