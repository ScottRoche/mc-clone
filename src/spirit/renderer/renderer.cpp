#include "renderer.h"

#include <string>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "core/log.h"

#include "buffer.h"
#include "shader.h"

namespace Spirit
{
	static unsigned int vertexArray;

	static unsigned int shaderId;

	static float windowWidth = 800.0f;  // Only doing this temporarily I know the size
	static float windowHeight = 600.0f; // Only doing this temporarily I know the size

	static VertexBuffer* vertexBuffer;

	void RendererInit()
	{

		float verticies[] = {
			// Front
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  // top-right

			// Top
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-left
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // back-left
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // front-right
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // back-right
			
			// Bottom
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-left
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // back-left
			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  // front-right
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // back-right

			// Back
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-left
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // top-right

			// Right
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-left
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // top-right

			// Left
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top-left
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // top-right
		};

		unsigned int indicies[] = {
			//0, 1, 2, 0, 1, 3,
			0, 1, 2,
			2, 0, 3,

			4, 5, 6,
			6, 7, 5,

			8, 9, 10,
			10, 11, 9,

			12, 13, 14,
			15, 12, 14,

			16, 17, 18,
			19, 16, 18,

			20, 21, 22,
			23, 20, 22
		};

		// Generate vertex attrib array
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		// Create vertex buffer
		vertexBuffer = new VertexBuffer(sizeof(verticies), verticies);

		// Vertex attribs
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		// Create index buffer
		IndexBuffer indexBuffer(sizeof(indicies), indicies);

		// File paths like this aren't good. Only for temporary testing.
		Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
		shaderId = shader.GetShaderId();

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		                                        windowWidth / windowHeight,
		                                        0.1f,
		                                        100.0f);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		int projLoc = glGetUniformLocation(shaderId, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		int viewLoc = glGetUniformLocation(shaderId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glEnable(GL_DEPTH_TEST);
		LOG_INFO("Renderer Initalised");
	}

	void RendererDeinit()
	{
		glBindVertexArray(0);
		LOG_INFO("Renderer Deinitalised");
	}

	void Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model,
		                    (float)glfwGetTime() * glm::radians(-20.0f),
		                    glm::vec3(1.0f, 1.0f, 0.0f));

		int modelLoc = glGetUniformLocation(shaderId, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(vertexArray);
		glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, 0);
	}
}