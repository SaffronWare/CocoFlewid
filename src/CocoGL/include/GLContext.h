#pragma once
#include <glad/gl.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "GLObject.h"



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
	std::vector<GLObject*> objects;
	
public:
	GLContext();
	~GLContext();

	bool Initialize();
};