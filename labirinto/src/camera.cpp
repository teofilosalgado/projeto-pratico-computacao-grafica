#include "camera.h"

Camera::Camera(float field_of_view, int window_width, int window_height, float mouse_sensitivity, float keyboard_sensitivity, glm::vec3 eye, glm::vec3 center)
{
	// Inicializa as variáveis
	this->eye = eye;
	this->center = center;

	this->mouse_sensitivity = mouse_sensitivity;
	this->keyboard_sensitivity = keyboard_sensitivity;
	this->jaw = -90.0;
	this->pitch = 0.0;

	this->up = glm::vec3(0.0, 1.0, 0.0);
	this->right = glm::vec3(1.0, 0.0, 0.0);
	
	// Matrix de projeção 
	//   Campo de visão: 45° 
	//   Aspecto: WINDOW_WIDTH/WINDOW_HEIGHT
	//   Intervalo de exibição: 0.1 <-> 100
	this->projection = glm::perspective(glm::radians(field_of_view), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
	set_view_matrix();
}

void Camera::set_view_matrix() {
	this->right = glm::normalize(glm::cross(this->center, glm::vec3(0.0, 1.0, 0.0)));
	this->up = glm::normalize(glm::cross(this->right, this->center));

	// Limita altura da câmera
	if (this->eye.y > 1.0f) {
		this->eye.y = 1.0f;
	}

	// Matrix da câmera (visão)
	this->view = glm::lookAt(
		this->eye,   // câmera se encontra em (x, y, z) no espaço
		this->eye + this->center,   // olhando para o centro
		this->up   // na orientação correta (cabeça pra cima)
	);
}

void Camera::move_center(float x_offset, float y_offset, double delta)
{
	// Calcula os ângulos de rotação vertical e horizontal (pitch e jaw)
	float local_x_offset = x_offset * delta * this->mouse_sensitivity;
	float local_y_offset = y_offset * delta * this->mouse_sensitivity;
	
	this->jaw += local_x_offset;
	this->pitch += local_y_offset;

	if (this->pitch > 45) {
		this->pitch = 45;
	}
	if (this->pitch < -45) {
		this->pitch = -45;
	}

	// Atualiza os vetores da câmera
	glm::vec3 local_center = glm::vec3(0.0, 0.0, 0.0);
	local_center.x = glm::cos(glm::radians(this->jaw)) * glm::cos(glm::radians(this->pitch));
	local_center.y = glm::sin(glm::radians(this->pitch));
	local_center.z = glm::sin(glm::radians(this->jaw)) * glm::cos(glm::radians(this->pitch));
	this->center = glm::normalize(local_center);

	set_view_matrix();
}

void Camera::move_eye(Direction direction, double delta)
{
	switch (direction)
	{
	case FORWARD:
		this->eye += this->center * (static_cast<float>(delta) * keyboard_sensitivity);
		break;
	case LEFT:
		this->eye -= this->right * (static_cast<float>(delta) * keyboard_sensitivity);
		break;
	case BACKWARD:
		this->eye -= this->center * (static_cast<float>(delta) * keyboard_sensitivity);
		break;
	case RIGHT:
		this->eye += this->right * (static_cast<float>(delta) * keyboard_sensitivity);
		break;
	default:
		break;
	}
	set_view_matrix();
}
