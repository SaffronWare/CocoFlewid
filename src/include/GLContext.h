#pragma once
#include <glad/gl.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

class ContextStorageTemplate
{
private:
public:
	ContextStorage();
	~ContextStorage();
};

class GLContext
{
private:
	std::vector<unsigned int> shaders;
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> ubos;
public:
	GLContext();
	~GLContext();

	bool Initialize();
};