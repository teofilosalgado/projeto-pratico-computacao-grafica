#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "shader.h"
#include "texture.h"
#include "model.h"
#include "scene.h"


constexpr int WINDOW_WIDTH = 720;
constexpr int WINDOW_HEIGHT = 480;
constexpr int MOUSE_SPEED = 0.000f;

int main(void) {
	GLFWwindow* window;

	// Inicializa a biblioteca GLFW
	if (!glfwInit())
		return -1;

	// Configura versão mínima do OpenGL e sampling de MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Cria uma nova janela
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Projeto de Computação Gráfica", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Define o contexto da janela
	glfwMakeContextCurrent(window);

	// Inicializa a biblioteca GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	// Define o método de leitura das teclas
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Esconde o cursor do mouse e libera o movimento completo
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Define a cor de fundo como preto
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Centraliza o cursor do mouse
	glfwPollEvents();
	glfwSetCursorPos(window, static_cast<float>(WINDOW_WIDTH) / 2.0f, static_cast<float>(WINDOW_HEIGHT) / 2.0f);

	// Ativa e configura o depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Ativa o culling
	glEnable(GL_CULL_FACE);

	// Cria e compila os shaders
	Shader* shader = new Shader("shaders\\default.vert", "shaders\\default.frag");
	// Cria uma câmera para a cena
	Camera* camera = new Camera(45.0f, WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	// Cria uma nova cena
	Scene* scene = new Scene(shader, camera);

	// Carrega a textura
	Texture* bricks_texture = new Texture("assets\\textures\\bricks.png");
	Texture* stone_texture = new Texture("assets\\textures\\stone.png");
	Texture* grass_texture = new Texture("assets\\textures\\grass.png");

	// Lê o modelo
	Model* cube_model = new Model("assets\\models\\cube", "cube.obj");

	// Cria um objeto para o cubo
	//Object* cube1 = new Object(cube_model, bricks_texture, 0.0f, 0.0f, 0.0f, 1.0f);
	//Object* cube2 = new Object(cube_model, stone_texture, -1.25f, -0.25f, 0.75f, 0.5f);
	Object* cube3 = new Object(cube_model, bricks_texture, glm::vec3(-2.0f, 0.0f, -2.0f), 1.0f);

	//scene->objects.push_back(cube1);
	//scene->objects.push_back(cube2);
	scene->objects.push_back(cube3);

	// Configuração do Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Enquanto o usuário não fechar a janela:
	while (!glfwWindowShouldClose(window)) {
		// Renderiza a cena
		scene->render();

		// Atualiza os valores necessários


		// Janela do ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Projeto de Computação Gráfica");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Troca os buffers
		glfwSwapBuffers(window);

		// Aguarda até que eventos ocorram
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}