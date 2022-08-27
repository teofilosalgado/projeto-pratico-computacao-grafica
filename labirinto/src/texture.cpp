#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "texture.h"

Texture::Texture(const char* texture_file_path)
{
    // Lendo o arquivo de textura
    int width = 0;
    int height = 0;
    stbi_uc* tex_data = NULL;
    std::cout << "Lendo textura: " << texture_file_path << std::endl;
    tex_data = stbi_load(texture_file_path, &width, &height, NULL, STBI_rgb_alpha);
    if (!tex_data) {
        std::cerr << "Erro ao ler o arquivo: " << texture_file_path << std::endl;
        std::cin;
    }
    std::cout << "Arquivo lido com sucesso" << std::endl;

    // Cria a textura
    std::cout << "Criando textura" << std::endl;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)tex_data);

    // Define os parâmetros de filtering e wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    std::cout << "Textura criada com sucesso" << std::endl;

    // Limpa o buffer
    if (tex_data) {
        stbi_image_free(tex_data);
    }
}
