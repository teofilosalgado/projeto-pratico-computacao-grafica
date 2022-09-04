#include "level.h"

static bool crystal_animation_cycle = false;
static int crystal_animation_count = 0;

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
	Texture* crystal_texture = new Texture("assets\\textures\\crystal.png");

	// Lê os modelos
	Model* map_model = new Model("assets\\models\\map", "map.obj");
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");
	Model* crystal_model = new Model("assets\\models\\crystal", "crystal.obj");

	// Cria os objetos
	Object* map = new Object(map_model, stone_texture, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Object* cube_1 = new Object(cube_model, bricks_texture, glm::vec3(5.0f, 0.25f, -8.0f), 0.25f);
	Object* cube_2 = new Object(cube_model, bricks_texture, glm::vec3(5.0f, 2.0f, -8.0f), 0.25f);
	Object* crystal = new Object(crystal_model, crystal_texture, glm::vec3(5.0f, 1.15f, -8.0f), 1.25f);

	scene->objects.push_back(map);
	scene->objects.push_back(cube_1);
	scene->objects.push_back(cube_2);
	scene->objects.push_back(crystal);

	this->is_ended = false;
}

void Level::run(bool is_paused)
{
	this->scene->render(is_paused);

	// Linha de chegada
	if (this->camera->eye.x >= 4.0f && this->camera->eye.x <= 6.0f && this->camera->eye.z <= -4.0f && this->camera->eye.z >= -6.0f) {
		this->is_ended = true;
	}

	// Inicia a animação coordenada do cristal
	if (this->is_ended) {
		scene->objects.at(1)->rotate(1.0, glm::vec3(0.0, 1.0, 0.0));
		scene->objects.at(2)->rotate(-1.0, glm::vec3(0.0, 1.0, 0.0));
		if (!crystal_animation_cycle) {
			if (crystal_animation_count >= 30) {
				crystal_animation_cycle = true;
			}
			crystal_animation_count++;
			scene->objects.at(3)->move(glm::vec3(0.0, 0.002, 0.0));
		}
		else {
			if (crystal_animation_count <= 0) {
				crystal_animation_cycle = false;
			}
			crystal_animation_count--;
			scene->objects.at(3)->move(glm::vec3(0.0, -0.002, 0.0));
		}
	}
}
