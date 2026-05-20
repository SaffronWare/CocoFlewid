#include "GLContext.h"


ContextStorageTemplate::ContextStorageTemplate() {}

ContextStorageTemplate::~ContextStorageTemplate() {}

GLContext::GLContext(){}

GLContext::~GLContext()
{
	for (GLObject* object : objects)
	{
		if (object)
		{
			delete (object);
		}
	}
	objects.clear();
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

