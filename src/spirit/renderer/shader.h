#pragma once

#include <string>

#include "glm.hpp"

namespace Spirit
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		void Bind();
		void Unbind();

		void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);

		unsigned int GetShaderId() const { return m_ShaderId; }

	private:
		std::string ReadFile(const std::string& filepath);
		void CompileShader(const std::string& vertexSource, const std::string& fragmentSource);

	private:
		unsigned int m_ShaderId;

		std::string m_VertexPath;
		std::string m_FragmentPath;
	};
}