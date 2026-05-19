#include "GLContext.h"


ContextStorageTemplate::ContextStorageTemplate() {}

ContextStorageTemplate::~ContextStorageTemplate() {}

GLContext::GLContext(){}

GLContext::~GLContext(){}

bool GLContext::Initialize()
{
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cerr << "Glad failedto load!\n";
		return false;
	}

	return true;
}

