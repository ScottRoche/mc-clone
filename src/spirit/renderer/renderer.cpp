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
#include "vertex_array.h"

static float s_SampleVerts[] = {
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

static unsigned int s_SampleIndicies[] = {
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

namespace Spirit
{
	struct RendererData
	{
		std::shared_ptr<VertexArray> RendererVertexArray;
		std::shared_ptr<VertexBuffer> RendererVertexBuffer;
		std::shared_ptr<Shader> RendererShader;
	};

	static float windowWidth = 800.0f;  // Only doing this temporarily I know the size
	static float windowHeight = 600.0f; // Only doing this temporarily I know the size

	static RendererData s_Data;

	void Renderer::Init()
	{
		s_Data.RendererVertexArray = std::make_shared<VertexArray>();
		s_Data.RendererVertexArray->Bind();

		s_Data.RendererVertexBuffer = std::make_shared<VertexBuffer>(sizeof(s_SampleVerts), s_SampleVerts);
		s_Data.RendererVertexBuffer->SetLayout({
			{3, ElementType::Float, false, (void*)0},
			{3, ElementType::Float, false, (void*)(3 * 4)}
		});
		s_Data.RendererVertexArray->AddVertexBuffer(s_Data.RendererVertexBuffer);

		std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(sizeof(s_SampleIndicies), s_SampleIndicies);
		s_Data.RendererVertexArray->SetIndexBuffer(indexBuffer);

		s_Data.RendererShader = std::make_shared<Shader>("./shaders/vertex.glsl", "./shaders/fragment.glsl");

		glEnable(GL_DEPTH_TEST);
		LOG_INFO("Renderer Initalised");

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		                                        windowWidth / windowHeight,
		                                        0.1f,
		                                        100.0f);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		int projLoc = glGetUniformLocation(s_Data.RendererShader->GetShaderId(), "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		int viewLoc = glGetUniformLocation(s_Data.RendererShader->GetShaderId(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}

	void Renderer::Deinit()
	{
		s_Data.RendererShader->Unbind();
		s_Data.RendererVertexBuffer->Unbind();
		s_Data.RendererVertexArray->Unbind();

		LOG_INFO("Renderer Deinitalised");
	}

	void Renderer::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model,
		                    (float)glfwGetTime() * glm::radians(-20.0f),
		                    glm::vec3(1.0f, 1.0f, 0.0f));

		int modelLoc = glGetUniformLocation(s_Data.RendererShader->GetShaderId(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	// void RendererInit()
	// {

	// 	// Generate vertex attrib array
	// 	vertexArray = new VertexArray();
	// 	vertexArray->Bind();

	// 	// Create vertex buffer
	// 	VertexBuffer vertexBuffer(sizeof(verticies), verticies);
	// 	vertexBuffer.SetLayout({
	// 		{3, ElementType::Float, false, (void*)0},
	// 		{3, ElementType::Float, false, (void*)(3 * 4)}
	// 	});

	// 	vertexArray->AddVertexBuffer(vertexBuffer); // Vertex attributes

	// 	// Create index buffer
	// 	IndexBuffer indexBuffer(sizeof(s_SampleIndicies), s_SampleIndicies);

	// 	// File paths like this aren't good. Only for temporary testing.
	// 	Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	// 	shaderId = shader.GetShaderId();

	// 	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
	// 	                                        windowWidth / windowHeight,
	// 	                                        0.1f,
	// 	                                        100.0f);

	// 	glm::mat4 view = glm::mat4(1.0f);
	// 	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// 	int projLoc = glGetUniformLocation(shaderId, "proj");
	// 	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// 	int viewLoc = glGetUniformLocation(shaderId, "view");
	// 	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// 	vertexBuffer.Unbind();
	// 	vertexArray->Unbind();
	// }

	// void RendererDeinit()
	// {
	// 	delete vertexArray;
	// 	glBindVertexArray(0);
	// 	LOG_INFO("Renderer Deinitalised");
	// }
}