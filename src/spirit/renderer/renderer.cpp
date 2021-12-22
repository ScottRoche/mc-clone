#include "renderer.h"

#include <string>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


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
		static const unsigned int CubeCount = 256 * (10 * 10);
		static const unsigned int MaxVerts = 24 * CubeCount;
		static const unsigned int MaxIndicies = 36 * CubeCount;

		unsigned int IndexCount = 0;

		VertexArray* RendererVertexArray;
		VertexBuffer* RendererVertexBuffer;
		Shader* RendererShader;
		IndexBuffer* RendererIndicies;
		std::vector<VertexData> RendererVertexData; // Vertex Data
	};

	static RendererData s_Data;

	void Renderer::Init()
	{
		s_Data.RendererVertexArray = new VertexArray();
		s_Data.RendererVertexArray->Bind();

		s_Data.RendererVertexBuffer = new VertexBuffer(sizeof(VertexData) * s_Data.MaxVerts);
		s_Data.RendererVertexBuffer->SetLayout({
			{3, ElementType::Float, false, (void*)0},
			{3, ElementType::Float, false, (void*)(3 * 4)}
		});

		s_Data.RendererVertexArray->AddVertexBuffer(s_Data.RendererVertexBuffer);

		uint32_t offset = 0;
		unsigned int indicies[s_Data.MaxIndicies];
		for (unsigned int i = 0; i < s_Data.MaxIndicies; i += 6)
		{
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;

			indicies[i + 3] = offset + 0;
			indicies[i + 4] = offset + 2;
			indicies[i + 5] = offset + 3;

			offset += 4;
		}
		s_Data.RendererIndicies = new IndexBuffer(s_Data.MaxIndicies * sizeof(unsigned int), indicies);

		s_Data.RendererShader = new Shader("./shaders/Cube_VP.glsl", "./shaders/Cube_FP.glsl");
	}

	void Renderer::Deinit()
	{
		delete s_Data.RendererVertexArray;
		delete s_Data.RendererVertexBuffer;
		delete s_Data.RendererShader;
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_Data.RendererShader->Bind();

		s_Data.RendererShader->SetUniformMatrix4fv("proj", camera.GetProjection());
		s_Data.RendererShader->SetUniformMatrix4fv("view", camera.GetViewMatrix());
	}

	void Renderer::EndScene()
	{
		LOG_WARN("Standard Flushing");
		Flush();
	}

	void Renderer::Submit(float* meshData, uint32_t dataSize)
	{
		static int sub_count = 0;
		VertexData vertexData;

		if (s_Data.IndexCount >= s_Data.MaxIndicies)
		{
			LOG_WARN("Premature Flushing ({:d}B)", sub_count);
			Flush();
			sub_count = 1;
		}
		else
		{
			sub_count++;
		}

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

		s_Data.IndexCount += 36;
	}

	void Renderer::SetViewportSize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::Flush()
	{
		s_Data.RendererVertexBuffer->AddData((float*)s_Data.RendererVertexData.data(),
		                                     s_Data.RendererVertexData.size() * sizeof(VertexData));
		Draw();

		s_Data.RendererVertexData.clear();
		s_Data.RendererVertexBuffer->Reset();
		s_Data.IndexCount = 0;
	}

	void Renderer::Draw()
	{
		s_Data.RendererShader->Bind();
		s_Data.RendererVertexArray->Bind();
		s_Data.RendererIndicies->Bind();

		glDrawElements(GL_TRIANGLES, s_Data.MaxIndicies, GL_UNSIGNED_INT, 0);
	}

}