#pragma once
#include <glad/gl.h>
#include <glfw3.h>
#include <iostream>

class GLContext
{
private:
public:
	GLContext();
	~GLContext();

	bool Initialize();
};