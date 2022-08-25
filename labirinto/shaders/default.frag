#version 330 core

// Valor de texture interpolado resultante do shader de v�rtice
in vec2 uv;

// Cor resultante da superf�cie
out vec3 color;

// Constante de unidade de textura
uniform sampler2D texture;

void main() {
	// A sa�da � definida como a cor na dada posi��o de uv
	color = texture(texture, uv, -2.0).rgb;
}