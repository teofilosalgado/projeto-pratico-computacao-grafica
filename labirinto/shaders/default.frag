#version 330 core

// Valores do shader de vértices
in vec3 fragment_position;
in vec2 fragment_uv;
in vec3 fragment_normal;
in vec3 fragment_light_position;

// Uniformes de iluminação
uniform vec3 light_intensity;

// Constante de unidade de textura
uniform sampler2D sampler;

// Cor resultante da superfície
out vec4 color;

void main() {
    // Luz ambiente
    float ambient_strength = 0.5;
    vec3 ambient = ambient_strength * light_intensity;

    // Luz difusa
    vec3 normal = normalize(fragment_normal);
    vec3 light_direction = normalize(fragment_light_position - fragment_position);
    float diffusion = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = diffusion * light_intensity;

    // Pixel resultante
    vec4 surface_color = texture(sampler, fragment_uv);
    color = vec4((ambient + diffuse) * surface_color.rgb, surface_color.a);
}