#include "camera.h"

Camera::Camera(float field_of_view, int window_width, int window_height, glm::vec3 eye, glm::vec3 center)
{
	// Inicializa as vari�veis
	this->eye = eye;
	this->center = center;

	this->mouse_sensitivity = 0.25;
	this->jaw = -90.0;
	this->pitch = 0.0;

	this->up = glm::vec3(0.0, 1.0, 0.0);
	this->right = glm::vec3(1.0, 0.0, 0.0);
	
	// Matrix de proje��o 
	//   Campo de vis�o: 45� 
	//   Aspecto: WINDOW_WIDTH/WINDOW_HEIGHT
	//   Intervalo de exibi��o: 0.1 <-> 100
	this->projection = glm::perspective(glm::radians(field_of_view), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

	// Matrix da c�mera (vis�o)
	this->view = glm::lookAt(
		this->eye,   // c�mera se encontra em (x, y, z) no espa�o
		this->center,   // olhando para o centro
		this->up   // na orienta��o correta (cabe�a pra cima)
	);
}

void Camera::move(float x_offset, float y_offset)
{
	// Calcula os �ngulos de rota��o vertical e horizontal (pitch e jaw)
	float local_x_offset = x_offset * this->mouse_sensitivity;
	float local_y_offset = y_offset * this->mouse_sensitivity;
	
	this->jaw += local_x_offset;
	this->pitch += local_y_offset;

	if (this->pitch > 45) {
		this->pitch = 45;
	}
	if (this->pitch < -45) {
		this->pitch = -45;
	}

	// Atualiza os vetores da c�mera
	glm::vec3 local_center = glm::vec3(0.0, 0.0, 0.0);
	local_center.x = glm::cos(glm::radians(this->jaw)) * glm::cos(glm::radians(this->pitch));
	local_center.y = glm::sin(glm::radians(this->pitch));
	local_center.z = glm::sin(glm::radians(this->jaw)) * glm::cos(glm::radians(this->pitch));

	this->center = glm::normalize(local_center);
	this->right = glm::normalize(glm::cross(this->center, glm::vec3(0.0, 1.0, 0.0)));
	this->up = glm::normalize(glm::cross(this->right, this->center));

	// Matrix da c�mera (vis�o)
	this->view = glm::lookAt(
		this->eye,
		this->eye + this->center,
		this->up
	);
}