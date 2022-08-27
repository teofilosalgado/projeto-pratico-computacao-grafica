#include "camera.h"

Camera::Camera(float field_of_view, int window_width, int window_height)
{
	// Matrix de proje��o 
	//   Campo de vis�o: 45� 
	//   Aspecto: WINDOW_WIDTH/WINDOW_HEIGHT
	//   Intervalo de exibi��o: 0.1 <-> 100
	this->projection = glm::perspective(glm::radians(field_of_view), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 1000.0f);

	// Matrix da c�mera (vis�o)
	this->view = glm::lookAt(
		glm::vec3(3, 3, 3),   // c�mera se encontra em (3, 3, 3) no espa�o
		glm::vec3(0, 0, 0),   // olhando para a origem
		glm::vec3(0, 1, 0)    // na orienta��o correta (cabe�a pra cima)
	);
}
