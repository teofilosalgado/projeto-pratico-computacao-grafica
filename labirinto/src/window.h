#pragma once
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

private:
	float width;
	float height;
	const char* title;
};

