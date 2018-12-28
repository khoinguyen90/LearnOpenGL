#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocations;
	// caching for uniforms
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);

	void SetUniform1i(const std::string& name, float value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
