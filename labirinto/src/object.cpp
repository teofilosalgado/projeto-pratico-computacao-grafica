#include "object.h"

Object::Object(Model* model, Texture* texture, glm::vec3 coordinates, float scale)
{
	this->model = model;
	this->texture = texture;
	this->scale = scale;
	this->coordinates = coordinates;
	this->position = glm::translate(glm::mat4(1.0f), this->coordinates);
}

void Object::move_to(glm::vec3 coordinates)
{
	this->coordinates = coordinates;
	this->position = glm::translate(glm::mat4(1.0f), this->coordinates);
}

void Object::move(glm::vec3 delta_coordinates)
{
	this->coordinates += delta_coordinates;
	this->position = glm::translate(glm::mat4(1.0f), this->coordinates);
}

void Object::rotate(float angle, glm::vec3 axis) {
	this->position = glm::rotate(this->position, glm::radians(angle), axis);
}