#pragma once
#include "shader.h"
#include "camera.h"
#include "object.h"
#include <vector>
class Scene
{
public:
	Scene(Shader* shader, Camera* camera);
	void add_object(Object* object);
private:
	Shader* shader;
	Camera* camera;
	std::vector<Object*> objects;

	GLuint model_uniform;
	GLuint view_uniform;
	GLuint projection_uniform;

	GLuint texture_uniform;
};

