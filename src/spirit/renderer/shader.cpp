#include "shader.h"

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/log.h"

namespace Spirit
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
		: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
	{
		std::string vertexSource = ReadFile(m_VertexPath);
		std::string fragmentSource = ReadFile(m_FragmentPath);

		if (vertexSource.empty() || fragmentSource.empty())
		{
			LOG_ERROR("Failed to create shader\nOne of the given source files was empty.");
			return;
		}

		m_ShaderId = glCreateProgram();
		CompileShader(vertexSource, fragmentSource);
		Bind();
	}

	void Shader::Bind()
	{
		glUseProgram(m_ShaderId);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::string source;
		std::ifstream shaderFile(filepath);
		size_t size = 0;

		if (shaderFile.is_open())
		{
			shaderFile.seekg(0, std::ios::end);
			size = shaderFile.tellg();
			shaderFile.seekg(0, std::ios::beg);
			source.resize(size);
			shaderFile.read((char*)source.data(), size);
			shaderFile.close();
		}

		return source;
	}

	void Shader::CompileShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		char* source = nullptr;
		int success;

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (char*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			LOG_ERROR("Shader Compilation Failed:\n{:s}", infoLog);
			return;
		}

		source = (char*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			LOG_ERROR("Shader Compilation Failed:\n{:s}", infoLog);
			return;
		}

		glAttachShader(m_ShaderId, vertexShader);
		glAttachShader(m_ShaderId, fragmentShader);
		glLinkProgram(m_ShaderId);

		glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(m_ShaderId, 512, NULL, infoLog);
			LOG_ERROR("Shader Linkage Failed:\n{:s}", infoLog);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}