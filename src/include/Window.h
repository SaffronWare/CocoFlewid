#pragma once
#include "GLContext.h"
#include "glfw3.h"
#include "imgui.h"
#include <iostream>
#include <functional>


class Window;

void default_error_callback(int error, const char* description);

bool default_loop(Window* window);


class Window
{
private:
	void (*err_callback)(int, const char*) = default_error_callback;
	unsigned int gl_version_major = 4;
	unsigned int gl_version_minor = 6;


	int window_width = 0;
	int window_height = 0;
	double dt = 0.0f;

	GLContext* context;

	bool (*loop)(Window*) = &default_loop;
	

	GLFWwindow* window;

public:
	Window(unsigned int GL_VERSION_MAJOR = 0, unsigned int GL_VERSION_MINOR = 0, bool(*loop)(Window*)=nullptr);
	~Window();

	GLContext* Initialize();
	void SetCallback(void (*new_err_callback)(int,const char*));
	void Run();

	double getDT();
	int getWidth();
	int getHeight();
	GLContext* getContext();
};