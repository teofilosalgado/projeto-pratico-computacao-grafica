#include "level.h"

Level::Level(Camera* camera)
{
	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");

	// Cria uma nova cena
	this->scene = new Scene(shader, camera);

	// Carrega a textura
	Texture* bricks_texture = new Texture("assets\\textures\\bricks.png");

	// Lê o modelo
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");

	// Cria um objeto para o cubo
	Object* cube = new Object(cube_model, bricks_texture, glm::vec3(-2.0f, 0.0f, -2.0f), 1.0f);
	scene->objects.push_back(cube);
}

void Level::run()
{
	this->scene->render();
}
