#pragma once
#include "GLObject.h"
#include "VBO.h"

class VAO : public GLObject
{
private:
public:
	VAO();
	~VAO();

	void SetSlot(unsigned int slot, unsigned int offset, VBO& vbo, 
		unsigned int size = 3, 
		GLenum type = GL_FLOAT, 
		GLboolean normalized = GL_FALSE, 
		GLsizei stride = 3* sizeof(float));

	void Initialize();
	void EnableSlot(unsigned int slot);
	void DisableSlot(unsigned int slot);
	void Bind();
	void Unbind();

};