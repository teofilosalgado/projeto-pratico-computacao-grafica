#include "object.h"

Object::Object(Model* model, Texture* texture, float x, float y, float z)
{
	this->model = model;
	this->texture = texture;
	this->position = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}
