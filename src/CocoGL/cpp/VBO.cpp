#include "VBO.h"

VBO::VBO() 
{
	this->type = GL_ARRAY_BUFFER;
	

}

void VBO::Initialize()
{
	glGenBuffers(1, &id);
}

VBO::~VBO()
{
	if (this->id)
	{
		glDeleteBuffers(1, &this->id);
	}
	this->id = 0;
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Data(float* vertices, unsigned int data_size, GLenum management)
{
	this->Bind();

	glBufferData(GL_ARRAY_BUFFER, data_size, vertices, management);

	this->Unbind();
}