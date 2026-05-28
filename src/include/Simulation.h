#pragma once

#include "CocoFramework.h"


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
		Shader enforcer;
		Shader advector;
		Shader copier;
		Shader windtunnel;

		
		PPTexture u_velocities;
		PPTexture v_velocities;
		PPTexture scalar_data;
		VAO vao;
		VBO vbo;

		unsigned int aspect_uniform;
		unsigned int v_uniform;
		unsigned int u_uniform;
		unsigned int scalar_uniform;
		unsigned int checker_type;
		unsigned int dt_uniform;
		unsigned int e_dt_uniform;
		unsigned int advector_grid_spacing_uniform;
		unsigned enforcer_grid_spacing_uniform;
		unsigned int frame = 0;


		void RunShader();
		void Copy();
		void Swap();


		void Init();
	};

	bool loop(Window* window);

};
