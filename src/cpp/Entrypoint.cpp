

#include "Window.h"
#include <iostream>


constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;


int main()
{
	Window window = Window(OPENGL_MAJOR, OPENGL_MINOR);

	GLContext* context = window.Initialize();


	window.Run();
}