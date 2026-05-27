#include "Simulation.h"


int main()
{
	Window window = Window(OPENGL_MAJOR, OPENGL_MINOR, Coco::loop);

	Coco::ContextStorage* storage = new Coco::ContextStorage();

	GLContext* context = window.Initialize(storage, 1000, 1000, true);

	storage->Init();

	window.Run();
}