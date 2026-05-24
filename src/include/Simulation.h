#pragma once

#include "CocoFramework.h"
#include "Fluid.h"

constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;
constexpr int num_particles_x = 100;
constexpr int num_particles_y = 50;



namespace Coco {


	extern const char* vertexShaderPath;
	extern const char* fragShaderPath;
	extern std::string vertexShaderSource;
	extern std::string fragmentShaderSource;


	extern float vertices[18];


	class ContextStorage : public ContextStorageTemplate
	{
	public:
		Shader shader;
		VAO vao;
		VBO vbo;
		Fluid fluid;

		unsigned int aspect_uniform;
		unsigned int fluid_texure_uniform;
		unsigned int density_texture_uniform;

		void Init();
	};

	bool loop(Window* window);

};
