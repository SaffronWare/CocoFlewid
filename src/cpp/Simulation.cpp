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
		u_uniform = shader.get_loc("UData");
		v_uniform = shader.get_loc("VData");
		scalar_uniform = shader.get_loc("SData");

		std::string enforcer_source = read_file("shaders/enforcer.glsl");
		enforcer.CreateCompute(enforcer_source.c_str());
		enforcer_grid_spacing_uniform = enforcer.get_loc("grid_spacing");
		checker_type = enforcer.get_loc("type");

		std::string advector_source = read_file("shaders/advector.glsl");
		advector.CreateCompute(advector_source.c_str());
		dt_uniform = advector.get_loc("dt");
		advector_grid_spacing_uniform = advector.get_loc("grid_spacing");

		std::string copier_source = read_file("shaders/copy.glsl");
		copier.CreateCompute(copier_source.c_str());

		
		u_velocities.Initialize(width/4, height/4, GL_R32F, GL_FLOAT);
		v_velocities.Initialize(width/4, height/4, GL_R32F, GL_FLOAT);
		scalar_data.Initialize(width/4, height/4, GL_RGBA32F, GL_FLOAT);

		vbo.Initialize();
		vbo.Data(vertices, sizeof(vertices));

		vao.Initialize();
		vao.SetSlot(0, 0, vbo, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		vao.EnableSlot(0);

		Shader AITest;
		std::string aitestcode = read_file("shaders/aitestcode.glsl");
		AITest.CreateCompute(aitestcode.c_str());
		AITest.Use();
		RunShader();
		Swap();
		

	}

	void ContextStorage::Copy()
	{
		copier.Use();
		RunShader();

	}

	void ContextStorage::RunShader()
	{
		u_velocities.BindImage(0, 1);
		v_velocities.BindImage(2, 3);
		scalar_data.BindImage(4, 5);
		glDispatchCompute((width + 15) / 16, (height + 15) / 16, 1);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
	}

	void ContextStorage::Swap()
	{
		u_velocities.Swap();
		v_velocities.Swap();
		scalar_data.Swap();
	}


	bool loop(Window* window)
	{

		ContextStorage* storage = static_cast<ContextStorage*>(window->storage);


		glfwPollEvents();

		glViewport(0, 0, window->getWidth(), window->getHeight());

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < 50; i++)
		{
			storage->Copy();
			storage->enforcer.Use();
			glUniform1i(storage->checker_type, i % 2);
			glUniform1f(storage->enforcer_grid_spacing_uniform, grid_spacing);
			storage->RunShader();
			storage->Swap();
		}

		storage->Copy();
		storage->advector.Use();
		glUniform1f(storage->dt_uniform, (float)window->getDT());
		glUniform1f(storage->advector_grid_spacing_uniform, grid_spacing);
		storage->RunShader();
		storage->Swap();
		
		storage->Copy();
		storage->shader.Use();
		storage->u_velocities.BindReadToSlot(0);
		storage->v_velocities.BindReadToSlot(1);
		storage->scalar_data.BindReadToSlot(2);
		glUniform1i(storage->u_uniform, 0);
		glUniform1i(storage->v_uniform, 1);
		glUniform1i(storage->scalar_uniform, 2);
		glUniform1f(storage->aspect_uniform, window->getAspect());


		storage->vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window->getWindow());

		//while (storage->frame > 1000) {};
		storage->frame += 1;
		return true;
	}
}

