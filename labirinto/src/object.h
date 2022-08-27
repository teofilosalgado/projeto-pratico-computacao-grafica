#pragma once
#include <string>
#include "texture.h"
#include "model.h"
class Object
{
public:
	Object(Model* model, Texture* texture, float x, float y, float z);
	glm::mat4 position;
	Model* model;
	Texture* texture;
};

