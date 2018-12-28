#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string & filepath)
	: m_FilePath(filepath)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniformMat4f(const std::string & name, glm::mat4& matrix)
{
	GLCall(unsigned int location = GetUniformLocation(name));
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string & name, float value)
{
	GLCall(unsigned int location = GetUniformLocation(name));
	GLCall(glUniform1i(location, value));
}

void Shader::SetUniform1f(const std::string & name, float value)
{
	GLCall(unsigned int location = GetUniformLocation(name));
	GLCall(glUniform1f(location, value));
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(unsigned int location = GetUniformLocation(name));
	GLCall(glUniform4f(location, v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
	{
		return m_UniformLocations[name];
	}

	GLCall(unsigned int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesnt't exist!" << std::endl;

	m_UniformLocations[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile shader!" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


