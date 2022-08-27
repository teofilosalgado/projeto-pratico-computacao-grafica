#pragma once
#include <string>
#include "texture.h"
#include "model.h"
class Object
{
public:
	Object(Model* model, Texture* texture, glm::vec3 coordinates, float scale);
	void move_to(glm::vec3 coordinates);
	void move(glm::vec3 delta_coordinates);

	glm::mat4 position;
	Model* model;
	Texture* texture;
	float scale;
	glm::vec3 coordinates;
};

