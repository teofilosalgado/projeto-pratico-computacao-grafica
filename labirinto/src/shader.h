#pragma once

#include <GL/glew.h>

class Shader {
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);

	GLuint program_id;
};
