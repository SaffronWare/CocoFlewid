#pragma once
#include <glad/gl.h>
#include <glfw3.h>

struct GLObject
{
protected:
	GLenum type = NULL;
	
public:
	unsigned int id = 0;
	GLObject() = default;
	virtual ~GLObject() = 0;

	unsigned int GetID();
	GLenum GetType();
};

inline GLObject::~GLObject() {}

inline unsigned int GLObject::GetID()
{
	return this->id;
}

inline GLenum GLObject::GetType()
{
	return this->type;
}