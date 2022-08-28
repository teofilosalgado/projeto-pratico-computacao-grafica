#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float field_of_view, int window_width, int window_height, glm::vec3 eye, glm::vec3 center);
	void move(float x_offset, float y_offset);

	float mouse_sensitivity;
	float jaw;
	float pitch;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 eye;    // position
	glm::vec3 center; // front
	glm::vec3 up;
	glm::vec3 right;
};

