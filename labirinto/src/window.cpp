#include "window.h"

// Lista de controles do jogo
static std::map<const char*, const char*> controls = {
	{"P", "Pausar"},
	{"Esc", "Sair"},
	{"W", "Andar pra frente"},
	{"S", "Andar pra trás"},
	{"A", "Andar pra esquerda"},
	{"D", "Andar pra direita"},
	{"L", "Ativar/desativar a iluminação"},
	{"Mouse", "Câmera"},
};

// Limite de FPS
constexpr float LIMITE_FPS = 60.0f;


static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int modifiers) {
	Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(handler->window, true);
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		handler->pause();
	}
	if (key == GLFW_KEY_L && action != GLFW_PRESS) {
		handler->level->scene->toggle_light();
	}

	if (key == GLFW_KEY_W && action != GLFW_RELEASE) {
		handler->level->camera->move_eye(FORWARD, handler->delta);
	}
	if (key == GLFW_KEY_A && action != GLFW_RELEASE) {
		handler->level->camera->move_eye(LEFT, handler->delta);
	}
	if (key == GLFW_KEY_S && action != GLFW_RELEASE) {
		handler->level->camera->move_eye(BACKWARD, handler->delta);
	}
	if (key == GLFW_KEY_D && action != GLFW_RELEASE) {
		handler->level->camera->move_eye(RIGHT, handler->delta);
	}

}

static void cursor_pos_callback(GLFWwindow* window, double x_position, double y_position) {
	Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (handler->is_paused) {
		return;
	}

	if (handler->first_mouse) {
		handler->last_cursor_x_position = x_position;
		handler->last_cursor_y_position = y_position;
		handler->first_mouse = false;
	}

	float x_offset = x_position - handler->last_cursor_x_position;
	float y_offset = handler->last_cursor_y_position - y_position;

	handler->last_cursor_x_position = x_position;
	handler->last_cursor_y_position = y_position;

	handler->level->camera->move_center(x_offset, y_offset, handler->delta);
}

Window::Window(float width, float height, const char* title) {
	// Inicializa os campos
	this->width = width;
	this->height = height;
	this->title = title;
	this->last_cursor_x_position = width / 2;
	this->last_cursor_y_position = height / 2;
	this->first_mouse = true;
	this->is_paused = true;
	this->last_time = 0;
	this->delta = 0;

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

	// Esconde o cursor do mouse e libera o movimento completo
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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

	// Nível do jogo
	this->level = new Level(this->width, this->height);
}

Window::~Window() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Window::pause() {
	if (this->is_paused) {
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	this->is_paused = !this->is_paused;
}

void Window::run() {
	while (!glfwWindowShouldClose(window)) {
		// Limita o FPS das cenas
		double current_time = glfwGetTime();
		this->delta = current_time - this->last_time;
		if (this->delta <= (1.0 / LIMITE_FPS)) {
			continue;
		}

		// Atualiza o contador de tempo
		this->last_time = current_time;

		// Renderiza as cenas
		level->run(this->is_paused);

		// Inicializa a janela do ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (this->is_paused) {
			ImGui::Begin(this->title);
			ImGui::Text("Bem vindo ao jogo Labirinto!");
			ImGui::Text("FPS: %.2f", 1.0/this->delta);
			ImGui::Text("Controles:");
			if (ImGui::BeginTable("controls", 2)) {
				for (std::pair<const char*, const char*> const& control : controls)
				{
					ImGui::TableNextColumn();
					ImGui::Text(control.first);
					ImGui::TableNextColumn();
					ImGui::Text(control.second);
				}
				
				ImGui::EndTable();
			}
			if (ImGui::Button("Retomar")) {
				this->pause();
			}
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Troca os buffers
		glfwSwapBuffers(window);

		// Aguarda até que eventos ocorram
		glfwPollEvents();
	}
}
