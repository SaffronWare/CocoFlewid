

#include "Window.h"
#include "GLContext.h"
#include <iostream>



constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;

class ContextStorage : public ContextStorageTemplate
{
public:
	GLint shader;
};


int main()
{
	

	Window window = Window(OPENGL_MAJOR, OPENGL_MINOR);
	ContextStorage* storage = new ContextStorage();
	GLContext* context = window.Initialize(storage);

	window.Run();
}