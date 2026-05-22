#include "Entrypoint.h"




void ContextStorage::Init()
{


	vertexShaderSource = read_file(vertexShaderPath);
	fragmentShaderSource = read_file(fragShaderPath);
	shader.CreatePipeline(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

	vbo.Initialize();
	vbo.Data(vertices, sizeof(vertices));

	vao.Initialize();
	vao.SetSlot(0, 0, vbo, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	vao.EnableSlot(0);


}


bool loop(Window* window)
{

	ContextStorage* storage = static_cast<ContextStorage*>(window->storage);


	glfwPollEvents();

	glViewport(0, 0, window->getWidth(), window->getHeight());

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	storage->shader.Use();
	storage->vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);


	glfwSwapBuffers(window->getWindow());


	return true;
}

int main()
{
	// create our window
	Window window = Window(OPENGL_MAJOR, OPENGL_MINOR, loop);

	// create our storage where all our opengl objects are stored
	ContextStorage* storage = new ContextStorage();


	// get the context and initialize everything with full control over main loop
	GLContext* context = window.Initialize(storage, true);

	// setup opengl since window is now initialized
	storage->Init();

	window.Run();
}