#include "level.h"

Level::Level(Camera* camera)
{
	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");

	// Cria uma nova cena
	this->scene = new Scene(shader, camera);

	// Carrega a textura
	Texture* bricks_texture = new Texture("assets\\textures\\bricks.png");
	Texture* stone_texture = new Texture("assets\\textures\\stone.png");

	// Lê o modelo
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");

	// Cria um objeto para o cubo
	Object* cube = new Object(cube_model, bricks_texture, glm::vec3(-2.0f, 0.0f, -2.0f), 1.0f);
	Object* cube2 = new Object(cube_model, stone_texture, glm::vec3(-3.0f, 0.0f, -1.0f), 1.0f);
	scene->objects.push_back(cube);
	scene->objects.push_back(cube2);
}

void Level::run(bool is_paused)
{
	this->scene->render(is_paused);
}
