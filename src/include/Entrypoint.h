#include "CocoFramework.h"

constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"} \n\0";

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

class ContextStorage : public ContextStorageTemplate
{
public:
	Shader shader;
	VAO vao;
	VBO vbo;

	void Init();
};

bool loop(Window* window);

int main();

