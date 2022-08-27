#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float field_of_view, int window_width, int window_height);
private:
	glm::mat4 projection;
	glm::mat4 view;
};

