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

namespace Spirit
{
	struct VertexData
	{
		glm::vec3 Transform;
		glm::vec3 Color;
	};

	struct RendererData
	{
		static const unsigned int MaxVerts = 1024;

		VertexArray* RendererVertexArray;
		VertexBuffer* RendererVertexBuffer;
		Shader* RendererShader;
		IndexBuffer* RendererIndicies;
		std::vector<VertexData> RendererVertexData; // Vertex Data
	};

	static float windowWidth = 800.0f;  // Only doing this temporarily I know the size
	static float windowHeight = 600.0f; // Only doing this temporarily I know the size

	static RendererData s_Data;

	void Renderer::Init(const Camera& camera)
	{
		s_Data.RendererVertexArray = new VertexArray();
		s_Data.RendererVertexArray->Bind();

		s_Data.RendererVertexBuffer = new VertexBuffer(sizeof(float) * s_Data.MaxVerts);
		s_Data.RendererVertexBuffer->SetLayout({
			{3, ElementType::Float, false, (void*)0},
			{3, ElementType::Float, false, (void*)(3 * 4)}
		});

		s_Data.RendererVertexArray->AddVertexBuffer(s_Data.RendererVertexBuffer);

		uint32_t offset = 0;
		unsigned int indicies[s_Data.MaxVerts * 6];
		for (unsigned int i = 0; i < s_Data.MaxVerts; i += 6)
		{
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;

			indicies[i + 3] = offset + 0;
			indicies[i + 4] = offset + 2;
			indicies[i + 5] = offset + 3;

			offset += 4;
		}
		s_Data.RendererIndicies = new IndexBuffer((sizeof(float) * s_Data.MaxVerts) * 6, indicies);

		s_Data.RendererShader = new Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

		int projLoc = glGetUniformLocation(s_Data.RendererShader->GetShaderId(), "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

		int viewLoc = glGetUniformLocation(s_Data.RendererShader->GetShaderId(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));
	}

	void Renderer::Deinit()
	{
		delete s_Data.RendererVertexArray;
		delete s_Data.RendererVertexBuffer;
		delete s_Data.RendererShader;
	}

	void Renderer::Submit(float* meshData, uint32_t dataSize)
	{
		VertexData vertexData;

		for (uint32_t i = 0; i < dataSize / sizeof(float); i += 6)
		{
			vertexData.Transform = glm::vec3(meshData[i],
			                                 meshData[i + 1],
			                                 meshData[i + 2]);

			vertexData.Color = glm::vec3(meshData[i + 3],
			                             meshData[i + 4],
			                             meshData[i + 5]);

			s_Data.RendererVertexData.push_back(vertexData);
		}

		s_Data.RendererVertexBuffer->AddData(meshData, dataSize);
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

		s_Data.RendererShader->Bind();
		s_Data.RendererVertexArray->Bind();

		glDrawElements(GL_TRIANGLES, s_Data.MaxVerts, GL_UNSIGNED_INT, 0);

		s_Data.RendererVertexData.clear();
	}
}