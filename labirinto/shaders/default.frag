#version 330 core

// Valores do shader de vértices
in vec3 fragment_position;
in vec2 fragment_uv;
in vec3 fragment_normal;

// Uniformes de iluminação
uniform vec3 light_position;
uniform vec3 light_intensity;

// Uniforme de modelo
uniform mat4 model;

// Constante de unidade de textura
uniform sampler2D sampler;

// Cor resultante da superfície
out vec4 color;

void main() {
	// Calcula a normal em coordenadas da cena
    mat3 normal_matrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normal_matrix * fragment_normal);

	// Calcula a posição do pixel em relação a cena
    vec3 position = vec3(model * vec4(fragment_position, 1));

	// Calcula o vetor da superfície até a fonte de iluminação
    vec3 surface_to_light = light_position - position;

	// Calcula o cosseno do ângulo de incidência
	float brightness = dot(normal, surface_to_light) / (length(surface_to_light) * length(normal));
    brightness = clamp(brightness, 0, 1);

	// Calcula a cor final do pixel com base em:
    // 1. O ângulo de incidência
    // 2. A intensidade da luz
    // 3. A textura
    vec4 surface_color = texture(sampler, fragment_uv);
    color = vec4(brightness * light_intensity * surface_color.rgb, surface_color.a);
}