#pragma once
#include <glad/gl.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"

class ContextStorageTemplate
{
private:
public:
	ContextStorageTemplate();
	~ContextStorageTemplate();
};

class GLContext
{
private:
	std::vector<Shader*> shaders;
	
public:
	GLContext();
	~GLContext();

	bool Initialize();
};