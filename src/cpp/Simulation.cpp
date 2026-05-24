#include "Simulation.h"
#include "Fluid.h"


namespace Coco {
	const char* vertexShaderPath = "shaders/vert.glsl";
	const char* fragShaderPath = "shaders/frag.glsl";
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 -1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};


	void ContextStorage::Init()
	{

		float x_spacing, y_spacing;
		x_spacing = 2.0f / num_particles_x;
		y_spacing = 2.0f / num_particles_y;

		float x = -1.0f;
		float y = -1.0f;

		
		

		vertexShaderSource = read_file(vertexShaderPath);
		fragmentShaderSource = read_file(fragShaderPath);
		shader.CreatePipeline(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

		shader.Use();
		aspect_uniform = shader.get_loc("AspectRatio");
		fluid_texure_uniform = shader.get_loc("FluidData");
		density_texture_uniform = shader.get_loc("DensityData");

		vbo.Initialize();
		vbo.Data(vertices, sizeof(vertices));

		vao.Initialize();
		vao.SetSlot(0, 0, vbo, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		vao.EnableSlot(0);

		fluid.Init(1000, 1000.0f/800.0f);

	}


	bool loop(Window* window)
	{

		ContextStorage* storage = static_cast<ContextStorage*>(window->storage);


		glfwPollEvents();

		glViewport(0, 0, window->getWidth(), window->getHeight());

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		storage->fluid.update((float)window->getDT());

		storage->shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,storage->fluid.data_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, storage->fluid.density_texture);
		glUniform1i(storage->fluid_texure_uniform, 0);
		glUniform1f(storage->aspect_uniform, window->getAspect());
		glUniform1i(storage->density_texture_uniform, 1);

		storage->vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());


		return true;
	}
}

