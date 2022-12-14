#pragma once
#include "shader.h"
#include "camera.h"
#include "object.h"
#include <vector>
class Scene
{
public:
	Scene(Shader* shader, Camera* camera);
	void render(bool is_paused);
	void toggle_light();
	
	Shader* shader;
	Camera* camera;
	std::vector<Object*> objects;

	GLuint model_uniform;
	GLuint view_uniform;
	GLuint projection_uniform;

	GLuint light_position_uniform;
	GLuint light_intensity_uniform;

	GLuint texture_uniform;

	GLuint scale_uniform;

	GLuint vertex_buffer;
	GLuint uv_buffer;
	GLuint normal_buffer;
private:
	bool is_light_on;
	glm::vec3 light_intensity;
};

