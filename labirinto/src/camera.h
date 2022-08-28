#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "direction.h"

class Camera
{
public:
	Camera(float field_of_view, int window_width, int window_height, float mouse_sensitivity, float keyboard_sensitivity, glm::vec3 eye, glm::vec3 center);
	void move_center(float x_offset, float y_offset, double delta);
	void move_eye(Direction direction, double delta);

	float keyboard_sensitivity;
	float mouse_sensitivity;
	float jaw;
	float pitch;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	glm::vec3 right;
private:
	void set_view_matrix();
};

