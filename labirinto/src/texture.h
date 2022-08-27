#pragma once

#include <iostream>

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
public:
	Texture(const char* texture_file_path);

	GLuint texture_id;
};

