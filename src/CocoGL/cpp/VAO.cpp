#include "VAO.h"

VAO::VAO()
{
	this->type = GL_VERTEX_ARRAY;
}

void VAO::Initialize()
{
	glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::SetSlot(unsigned int slot, unsigned int offset, VBO& vbo, unsigned int size, GLenum type, GLboolean normalized, GLsizei stride)
{
	if (slot < 16)
	{
		Bind();
		vbo.Bind();

		glVertexAttribPointer(slot, size, type, normalized, stride, (void*)(offset));

		Unbind();
		vbo.Unbind();
	}
	else
	{
		std::cerr << "Only 16 slots allowed per VAO!\n";
	}
	
}

void VAO::EnableSlot(unsigned int slot)
{
	Bind();
	glEnableVertexAttribArray(slot);
	Unbind();
}

void VAO::DisableSlot(unsigned int slot)
{
	Bind();
	glDisableVertexAttribArray(slot);
	Unbind();
}