#include "Simulation.h"


const int width = 1000;
const int height = 800;
const float grid_spacing = 2.0f / height;


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
		data_uniform = shader.get_loc("FluidData");

		std::string enforcer_source = read_file("shaders/enforcer.glsl");
		enforcer.CreateCompute(enforcer_source.c_str());
		enforcer_grid_spacing_uniform = enforcer.get_loc("grid_spacing");
		checker_type = enforcer.get_loc("type");

		std::string advector_source = read_file("shaders/advector.glsl");
		advector.CreateCompute(advector_source.c_str());
		dt_uniform = advector.get_loc("dt");
		advector_grid_spacing_uniform = advector.get_loc("grid_spacing");
		
		glGenTextures(1, &write_texture);
		glBindTexture(GL_TEXTURE_2D, write_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

		glGenTextures(1, &read_texture);
		glBindTexture(GL_TEXTURE_2D, read_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

		vbo.Initialize();
		vbo.Data(vertices, sizeof(vertices));

		vao.Initialize();
		vao.SetSlot(0, 0, vbo, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		vao.EnableSlot(0);

	

	}

	void ContextStorage::Swap()
	{
		unsigned int temp = write_texture;
		write_texture = read_texture;
		read_texture = temp;
	}

	void ContextStorage::RunShader()
	{
		glBindImageTexture(0, write_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, read_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glDispatchCompute((width + 15) / 16, (height + 15) / 16, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
		Swap();
	}


	bool loop(Window* window)
	{

		ContextStorage* storage = static_cast<ContextStorage*>(window->storage);


		glfwPollEvents();

		glViewport(0, 0, window->getWidth(), window->getHeight());

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < 10; i++)
		{

			storage->enforcer.Use();
			glUniform1i(storage->checker_type, i % 2);
			glUniform1f(storage->enforcer_grid_spacing_uniform, grid_spacing);
			storage->RunShader();
		}

		storage->advector.Use();
		glUniform1f(storage->dt_uniform, (float)window->getDT());
		glUniform1f(storage->advector_grid_spacing_uniform, grid_spacing);

		storage->RunShader();
		

		storage->shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,storage->read_texture);
		glUniform1i(storage->data_uniform, 0);
		glUniform1f(storage->aspect_uniform, window->getAspect());


		storage->vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());


		return true;
	}
}

