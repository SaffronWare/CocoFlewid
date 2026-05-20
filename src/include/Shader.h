#pragma once
#include <glad/gl.h>

class Shader
{
private:
	GLint programID;
public:
	Shader();
	~Shader();

	void attachVertexShader(const char* source);
	void attachFragmentShader(const char* source);
	void attachComputeShader(const char* source);



};