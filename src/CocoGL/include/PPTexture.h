#pragma once
#include <glad/gl.h>
#include "Texture.h"

class PPTexture
{
private:
	Texture t0;
	Texture t1;
	int swap = 0;
public:
	PPTexture();
	~PPTexture();

	void Initialize(unsigned int width, unsigned int height, GLenum format = GL_RGBA32F, GLenum type = GL_FLOAT);
	void BindImage(unsigned int read_slot, unsigned int write_slot);
	void BindSlot(unsigned int read_slot, unsigned int write_slot);
	void BindReadToSlot(unsigned int slot);
	
};