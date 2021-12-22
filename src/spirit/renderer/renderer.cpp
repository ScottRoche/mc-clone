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
		static const unsigned int MaxVerts = 1024;

		unsigned int VertexCount = 0;

		VertexArray* RendererVertexArray;
		VertexBuffer* RendererVertexBuffer;
		Shader* RendererShader;
		IndexBuffer* RendererIndicies;
		std::vector<VertexData> RendererVertexData; // Vertex Data
	};

	static float windowWidth = 800.0f;  // Only doing this temporarily I know the size
	static float windowHeight = 600.0f; // Only doing this temporarily I know the size

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
		s_Data.RendererIndicies = new IndexBuffer(sizeof(VertexData) * s_Data.MaxVerts, indicies);

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
		VertexData vertexData;

		if (s_Data.VertexCount + (dataSize / sizeof(VertexData)) >= s_Data.MaxVerts)
		{
			LOG_WARN("Premature Flushing");
			Flush();
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

		s_Data.VertexCount += dataSize / sizeof(VertexData);
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
		s_Data.VertexCount = 0;
	}

	void Renderer::Draw()
	{
		s_Data.RendererShader->Bind();
		s_Data.RendererVertexArray->Bind();

		glDrawElements(GL_TRIANGLES, s_Data.MaxVerts, GL_UNSIGNED_INT, 0);
	}

}