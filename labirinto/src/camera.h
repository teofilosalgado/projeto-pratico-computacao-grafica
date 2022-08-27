#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float field_of_view, int window_width, int window_height, glm::vec3 eye, glm::vec3 center);
	void move_eye_to(glm::vec3 eye);
	void move_center_to(glm::vec3 center);

	void move_eye(glm::vec3 delta_eye);
	void move_center(glm::vec3 delta_center);


	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 eye;
	glm::vec3 center;
};

