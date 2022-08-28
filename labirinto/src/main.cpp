#include "window.h"

constexpr int WINDOW_WIDTH = 720;
constexpr int WINDOW_HEIGHT = 480;
constexpr const char* WINDOW_TITLE = "Projeto de Computação Gráfica";


int main(void) {
	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	window->run();
}