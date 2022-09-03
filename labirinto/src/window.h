#pragma once
#include <map>

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "camera.h"
#include "level.h"

class Window
{
public:
	Window(float width, float height, const char* title);
	~Window();
	void run();
	GLFWwindow* window;
	Level* level;
	void pause();
	bool is_paused;

	// Controles para a câmera
	float last_cursor_x_position;
	float last_cursor_y_position;
	bool first_mouse;

	// Controle de FPS
	double last_time;
	double delta;

private:
	float width;
	float height;
	const char* title;
};

