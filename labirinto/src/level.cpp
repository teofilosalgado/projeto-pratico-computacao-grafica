#include "level.h"

Level::Level(Camera* camera)
{
	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");

	// Cria uma nova cena
	this->scene = new Scene(shader, camera);

	// Carrega a textura
	Texture* white_texture = new Texture("assets\\textures\\white.png");

	// Lê o modelo
	Model* map_model = new Model("assets\\models\\map", "map.obj");
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");

	// Cria um objeto para o cubo
	Object* map = new Object(map_model, white_texture, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Object* cube = new Object(cube_model, white_texture, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	scene->objects.push_back(cube);
}

void Level::run(bool is_paused)
{
	this->scene->render(is_paused);
}
