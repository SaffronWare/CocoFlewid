#include "GLContext.h"


ContextStorageTemplate::ContextStorageTemplate() {}

ContextStorageTemplate::~ContextStorageTemplate() {}

GLContext::GLContext(){}

GLContext::~GLContext()
{
	for (Shader* shader : shaders)
	{
		if (shader)
		{
			delete (shader);
		}
	}
	shaders.clear();
}

bool GLContext::Initialize()
{
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cerr << "Glad failedto load!\n";
		return false;
	}

	return true;
}

