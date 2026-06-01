#include "PPTexture.h"


PPTexture::PPTexture()
{

}

PPTexture::~PPTexture()
{
	t0.~Texture();
	t1.~Texture();

}

void PPTexture::Initialize(unsigned int width, unsigned int height, GLenum format, GLenum type)
{
	t0.Initialize(width, height, format, type);
	t1.Initialize(width, height, format, type);
}

void PPTexture::BindImage(unsigned int slot0, unsigned int slot1)
{
	
	if (swap % 2 == 0)
	{
		t0.BindImage(slot0);
		t1.BindImage(slot1);
	}
	else
	{
		t0.BindImage(slot1);
		t1.BindImage(slot0);
	}
	

}

void PPTexture::BindSlot(unsigned int slot0, unsigned int slot1) 
{
	if (swap % 2 == 0)
	{
		t0.BindSlot(slot0);
		t1.BindSlot(slot1);
	}
	else
	{
		t0.BindSlot(slot1);
		t1.BindSlot(slot0);
	}
	
}

void PPTexture::BindReadToSlot(unsigned int slot)
{
	if (swap % 2 == 0)
	{
		t0.BindSlot(slot);
	}
	else
	{
		t1.BindSlot(slot);
	}
}

void PPTexture::Swap()
{
	swap += 1;
}


//