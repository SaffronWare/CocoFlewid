#include "Simulation.h"


int main()
{
	Window window = Window(OPENGL_MAJOR, OPENGL_MINOR, Coco::loop);

	Coco::ContextStorage* storage = new Coco::ContextStorage();

	GLContext* context = window.Initialize(storage, true);

	storage->Init();

	window.Run();
}