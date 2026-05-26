#pragma once
#include <glad/gl.h>
#include "GLObject.h"

class Texture : public GLObject
{
	GLenum format;
	GLenum dtype;
public:
	Texture();
	~Texture();
	void Initialize(unsigned int width, unsigned int height, GLenum format = GL_RGBA32F, GLenum type = GL_FLOAT);
	void BindImage(unsigned int slot);
	void BindSlot(unsigned int slot);
	void Bind();

};