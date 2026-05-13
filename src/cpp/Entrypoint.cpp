
#include "glad.h"
#include "glfw3.h"
#include "imgui.h"
#include <iostream>

void error_callback(int error, const char* description) {
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

int main()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cerr << "whoopsies! Glfw didnt init!\n";
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);


	GLFWwindow* window = glfwCreateWindow(1000, 800, "CocoFluid", NULL, NULL);
	if (!window)
	{
		std::cerr << "Whoopsies! window didnt create!\n";
	}
	

	glfwMakeContextCurrent(window);

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Glad failedto load!\n";
	}

	glViewport(0, 0, 1000, 800);
;
	

	int window_width, window_height;
	while (!glfwWindowShouldClose(window))
	{
	

		glfwGetWindowSize(window, &window_width, &window_height);
		glViewport(0, 0, window_width, window_height);

		glClearColor(1, 0, 0, 1);

	}
	glfwDestroyWindow(window);
}