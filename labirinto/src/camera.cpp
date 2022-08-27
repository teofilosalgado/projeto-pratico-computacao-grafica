#include "camera.h"

Camera::Camera(float field_of_view, int window_width, int window_height, glm::vec3 eye, glm::vec3 center)
{
	// Inicializa as vari�veis
	this->eye = eye;
	this->center = center;
	
	// Matrix de proje��o 
	//   Campo de vis�o: 45� 
	//   Aspecto: WINDOW_WIDTH/WINDOW_HEIGHT
	//   Intervalo de exibi��o: 0.1 <-> 100
	this->projection = glm::perspective(glm::radians(field_of_view), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 1000.0f);

	// Matrix da c�mera (vis�o)
	this->view = glm::lookAt(
		this->eye,   // c�mera se encontra em (x, y, z) no espa�o
		this->center,   // olhando para o centro
		glm::vec3(0, 1, 0)    // na orienta��o correta (cabe�a pra cima)
	);
}

void Camera::move_eye_to(glm::vec3 eye)
{
	this->eye = eye;
	this->view = glm::lookAt(
		this->eye,  
		this->center,
		glm::vec3(0, 1, 0)
	);
}

void Camera::move_center_to(glm::vec3 center)
{
	this->center = center;
	this->view = glm::lookAt(
		this->eye,
		this->center,
		glm::vec3(0, 1, 0)
	);
}

void Camera::move_eye(glm::vec3 delta_eye)
{
	this->eye += delta_eye;
	this->view = glm::lookAt(
		this->eye,
		this->center,
		glm::vec3(0, 1, 0)
	);
}

void Camera::move_center(glm::vec3 delta_center)
{
	this->center += delta_center;
	this->view = glm::lookAt(
		this->eye,
		this->center,
		glm::vec3(0, 1, 0)
	);
}
