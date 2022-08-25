#pragma once
#include <GL/glew.h>
class Texture
{
public:
	Texture(const char* texture_file_path);

	GLuint texture_id;
};

