#include "window.h"

static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int modifiers)
{
	Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handler->window, true);
}

static void cursor_pos_callback(GLFWwindow* window, double x_position, double y_position)
{
	Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

	if (handler->first_mouse) {
		handler->last_cursor_x_position = x_position;
		handler->last_cursor_y_position = y_position;
		handler->first_mouse = false;
	}

	float x_offset = x_position - handler->last_cursor_x_position;
	float y_offset = handler->last_cursor_y_position - y_position;

	handler->last_cursor_x_position = x_position;
	handler->last_cursor_y_position = y_position;

	handler->camera->move(x_offset, y_offset);
}

Window::Window(float width, float height, const char* title)
{
	// Inicializa os campos
	this->width = width;
	this->height = height;
	this->title = title;
	this->last_cursor_x_position = width / 2;
	this->last_cursor_y_position = height / 2;
	this->first_mouse = true;

	// Inicializa a biblioteca GLFW
	glfwInit();

	// Configura versão mínima do OpenGL e sampling de MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Cria uma nova janela
	this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
	if (!this->window) {
		glfwTerminate();
	}
	glfwSetWindowUserPointer(this->window, reinterpret_cast<void*>(this));

	// Define o contexto da janela
	glfwMakeContextCurrent(this->window);

	// Inicializa a biblioteca GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
	}

	// Define o método de leitura das teclas
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	// Esconde o cursor do mouse e libera o movimento completo
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Define a cor de fundo como preto
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Centraliza o cursor do mouse
	glfwSetCursorPos(this->window, static_cast<float>(this->width) / 2.0f, static_cast<float>(this->height) / 2.0f);

	// Ativa e configura o depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Ativa o culling
	glEnable(GL_CULL_FACE);

	// Configurações de callbacks de mouse e teclado
	glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, cursor_pos_callback);

	// Configuração do Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Cria uma câmera para as cenas
	this->camera = new Camera(45.0f, this->width, this->height, glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Window::run()
{
	// Nível do jogo
	Level* level = new Level(camera);

	while (!glfwWindowShouldClose(window)) {
		// Renderiza a cena
		level->run();

		// Inicializa a janela do ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin(this->title);
		// Renderiza os widgets da cena

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Troca os buffers
		glfwSwapBuffers(window);

		// Aguarda até que eventos ocorram
		glfwPollEvents();
	}
}
