#pragma once
#include <glad/gl.h>
#include "GLObject.h"
#include <iostream>

class Shader : public GLObject
{

public:
	Shader();
	void CreatePipeline(const char* vertex_source, const char* fragment_source);
	void CreateCompute(const char* compue_source);
	~Shader();

	void Use();

	static unsigned int compile_shader(const char* shader_source, GLenum shader_type);



};