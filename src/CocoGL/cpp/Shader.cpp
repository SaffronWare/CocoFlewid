#include "Shader.h"

Shader::Shader()
{
	this->type = GL_SHADER;
}

void Shader::CreatePipeline(const char* vertex_source, const char* fragment_source)
{
	this->id = glCreateProgram();

	unsigned int vertex_shader = Shader::compile_shader(vertex_source, GL_VERTEX_SHADER);
	unsigned int fragment_shader = Shader::compile_shader(fragment_source, GL_FRAGMENT_SHADER);

	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glLinkProgram(id);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(id);
}



void Shader::CreateCompute(const char* compute_source)
{
	this->id = glCreateProgram();
	this->type = GL_SHADER;
	unsigned int compute_shader = Shader::compile_shader(compute_source, GL_COMPUTE_SHADER);

	glAttachShader(id, compute_shader);
	glLinkProgram(id);

	glDeleteShader(compute_shader);
}

Shader::~Shader() 
{
	glDeleteProgram(id);
	this->type = NULL;
	this->id = 0;
}

unsigned int Shader::compile_shader(const char* source, GLenum type)
{
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::Use()
{
	glUseProgram(id);
}

