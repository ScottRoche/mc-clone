#include "renderer.h"

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/log.h"

#include "shader.h"

namespace Spirit
{
	static unsigned int vertexArray;

	void RendererInit()
	{
		float verticies[] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, // top-left
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f  // top-right
		};
		
		unsigned int indicies[] = {
			0, 1, 2,
			3, 0, 2
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		// Create index buffer
		unsigned int indexBuffer;
		glGenBuffers(2, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indicies, GL_STATIC_DRAW);

		// File paths like this aren't good. Only for temporary testing.
		Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		LOG_INFO("Renderer Initalised");
	}

	void RendererDeinit()
	{
		glBindVertexArray(0);
		LOG_INFO("Renderer Deinitalised");
	}

	void Draw()
	{
		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}