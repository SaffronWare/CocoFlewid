#include "Simulation.h"


const int width = 1000;
const int height = 800;


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

		
		glGenTextures(1, &write_texture);
		glBindTexture(GL_TEXTURE_2D, write_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width+1, height+1, 0, GL_RGBA, GL_FLOAT, nullptr);

		glGenTextures(1, &read_texture);
		glBindTexture(GL_TEXTURE_2D, read_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width+1, height+1, 0, GL_RGBA, GL_FLOAT, nullptr);

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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,storage->velocity_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, storage->scalar_texture);
		glUniform1i(storage->velocity_texure_uniform, 0);
		glUniform1f(storage->aspect_uniform, window->getAspect());
		glUniform1i(storage->scalar_texture_uniform, 1);

		storage->vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());


		return true;
	}
}

