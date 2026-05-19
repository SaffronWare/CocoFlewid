#include "Window.h"


bool default_loop(Window* window)
{
	std::cout << "Running!\n";
	return true;
}

void default_error_callback(int error, const char* description) {
	std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}


Window::Window(unsigned int GL_VERSION_MAJOR, unsigned int GL_VERSION_MINOR, bool(*loop)(Window*))
{
	if (GL_VERSION_MAJOR && GL_VERSION_MINOR)
	{
		this->gl_version_major = GL_VERSION_MAJOR;
		this->gl_version_minor = GL_VERSION_MINOR;
	}

	if (loop)
	{
		this->loop = loop;
	}

	

	if (!glfwInit())
	{
		std::cerr << "whoopsies! Glfw didnt init!\n";
	}

	glfwSetErrorCallback(this->err_callback);

	context = new GLContext();

}

Window::~Window()
{
	delete context;

	if (this->window)
	{
		glfwDestroyWindow(this->window);
	}
	glfwTerminate();
	
}

GLContext* Window::Initialize()
{


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);

	window = glfwCreateWindow(1000, 800, "CocoFluid", NULL, NULL);
	if (!window)
	{
		std::cerr << "Whoopsies! window didnt create!\n";
	}


	glfwMakeContextCurrent(window);

	if (context->Initialize())
		return context;
	return nullptr;

}

void Window::SetCallback(void(*new_err_callback)(int, const char*))
{
	this->err_callback = new_err_callback;
	glfwSetErrorCallback(this->err_callback);
}

void Window::Run()
{
	bool should_continue = true;

	while (!glfwWindowShouldClose(this->window) && should_continue)
	{
		
		glfwPollEvents();
		glfwGetWindowSize(window, &window_width, &window_height);
		glViewport(0, 0, window_width, window_height);

		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		should_continue = (*(this->loop))(this);

		glfwSwapBuffers(window);
	}
}

int Window::getWidth()
{
	return window_width;
}

int Window::getHeight()
{
	return window_height;
}

double Window::getDT()
{
	return dt;
}

GLContext* Window::getContext()
{
	return context;
}