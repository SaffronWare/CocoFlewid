#pragma once
#include <glad/gl.h>
#include "GLContext.h"

class VBO : public GLObject
{

public:
	VBO();
	~VBO();
	
	void Bind();

	void Unbind();

	void Initialize();

	void Data(float* vertices, unsigned int data_size, GLenum management = GL_STATIC_DRAW);
};