#pragma once

#include "CocoFramework.h"
#include "Fluid.h"

constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;



namespace Coco {

	extern Fluid fluid;

	extern const char* vertexShaderPath;
	extern const char* fragShaderPath;
	extern std::string vertexShaderSource;
	extern std::string fragmentShaderSource;

	extern float vertices[9];


	class ContextStorage : public ContextStorageTemplate
	{
	public:
		Shader shader;
		VAO vao;
		VBO vbo;

		void Init();
	};

	bool loop(Window* window);

};
