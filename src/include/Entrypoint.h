#include "CocoFramework.h"

constexpr int OPENGL_MAJOR = 4;
constexpr int OPENGL_MINOR = 6;


const char* vertexShaderPath = "shaders/vert.glsl";
const char* fragShaderPath = "shaders/frag.glsl";
std::string vertexShaderSource;
std::string fragmentShaderSource;

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

