#version 330 core

// Valor de texture interpolado resultante do shader de vértice
in vec2 uv;

// Cor resultante da superfície
out vec3 color;

// Constante de unidade de textura
uniform sampler2D texture;

void main() {
	// A saída é definida como a cor na dada posição de uv
	color = texture(texture, uv, -2.0).rgb;
}