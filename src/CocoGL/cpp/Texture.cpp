#include "Texture.h"

Texture::Texture() 
{
	this->type = GL_TEXTURE_2D;
}

Texture::~Texture() 
{
	glDeleteTextures(1, &id);
}

void Texture::Initialize(unsigned int width, unsigned int height, GLenum format, GLenum type)
{
	
	this->dtype = type;
	this->format = format;
	this->GetType();
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, type, nullptr);
}

void Texture::BindImage(unsigned int slot)
{
	glBindImageTexture(slot, id, 0, GL_FALSE, 0, GL_READ_WRITE, format);
}

void Texture::BindSlot(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}