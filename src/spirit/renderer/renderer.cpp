#include "renderer.h"

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/log.h"

namespace Spirit
{
	static unsigned int shaderProgram;
	static unsigned int vertexArray;

	static const char* vertexSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	static const char* fragmentSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	static bool CreateShader(unsigned int* shaderId,
	                         GLenum shaderType,
	                         const char* shaderSource)
	{
		int success;

		*shaderId = glCreateShader(shaderType);
		glShaderSource(*shaderId, 1, &shaderSource, NULL);
		glCompileShader(*shaderId);

		glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(*shaderId, 512, NULL, infoLog);
			LOG_ERROR("Shader Compilation Failed:\n{:s}", infoLog);
			return false;
		}

		return true;
	}

	void RendererInit()
	{
		float verticies[] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.0f,  0.5f, 0.0f  // top   
		};

		// Generate vertex attrib array
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		// Create vertex buffer
		unsigned int vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		// Vertex attribs
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		// Shaders
		unsigned int vertexShader, fragmentShader;
		if (!CreateShader(&vertexShader, GL_VERTEX_SHADER, vertexSource)
		    || !CreateShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentSource))
		{
			LOG_ERROR("Failed to initalise renderer");
			return;
		}

		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			LOG_ERROR("Shader Linkage Failed:\n{:s}", infoLog);
			return;
		}

		glUseProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void RendererDeinit()
	{
		glBindVertexArray(0);
	}

	void Draw()
	{
		glUseProgram(shaderProgram);
		glBindVertexArray(vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}