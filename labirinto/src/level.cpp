#include "level.h"

Level::Level(float width, float height)
{
	// Cria uma câmera para as cenas
	this->camera = new Camera(45.0f, width, height, 5.0, 10.0, glm::vec3(-5.0f, 1.0f, 8.0f), glm::vec3(-5.0f, 1.0f, 7.0f));

	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");

	// Cria uma nova cena
	this->scene = new Scene(shader, this->camera);

	// Carrega as texturas
	Texture* stone_texture = new Texture("assets\\textures\\stone.png");
	Texture* bricks_texture = new Texture("assets\\textures\\bricks.png");

	// Lê os modelos
	Model* map_model = new Model("assets\\models\\map", "map.obj");
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");

	// Cria os objetos
	Object* map = new Object(map_model, stone_texture, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Object* chest = new Object(cube_model, bricks_texture, glm::vec3(5.0f, 0.25f, -8.0f), 0.25f);
	scene->objects.push_back(map);
	scene->objects.push_back(chest);

	this->is_ended = false;
}

void Level::run(bool is_paused)
{
	this->scene->render(is_paused);

	// Linha de chegada
	if (this->camera->eye.x >= 4.0f && this->camera->eye.x <= 6.0f && this->camera->eye.z <= -4.0f && this->camera->eye.z >= -6.0f) {
		this->is_ended = true;
	}

	if (this->is_ended) {

	}
}
