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
#include "texture.h"

namespace Spirit
{
	struct VertexData
	{
		glm::vec3 Transform;
		glm::vec3 Color;
		glm::vec2 TexCoords;
		float TexIndex;
	};

	struct RendererData
	{
		static const unsigned int QuadCount = 20000;
		static const unsigned int MaxVerts = QuadCount * 4;
		static const unsigned int MaxIndicies = QuadCount * 6;

		unsigned int IndexCount = 0;

		VertexArray* RendererVertexArray;
		VertexBuffer* RendererVertexBuffer;
		Shader* RendererShader;
		IndexBuffer* RendererIndicies;
		std::vector<VertexData> RendererVertexData;
	};

	static RendererData s_Data;

	uint32_t indicies[s_Data.MaxIndicies];

	void Renderer::Init()
	{
		s_Data.RendererVertexArray = new VertexArray();
		s_Data.RendererVertexArray->Bind();

		s_Data.RendererVertexBuffer = new VertexBuffer(sizeof(VertexData) * s_Data.MaxVerts);
		s_Data.RendererVertexBuffer->SetLayout({
			{3, ElementType::Float, false, (void*)0},
			{3, ElementType::Float, false, (void*)(3 * 4)},
			{2, ElementType::Float, false, (void*)(6 * 4)},
			{1, ElementType::Float, false, (void*)(8 * 4)}
		});

		s_Data.RendererVertexArray->AddVertexBuffer(s_Data.RendererVertexBuffer);

		uint32_t offset = 0;
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
		s_Data.RendererIndicies = new IndexBuffer(indicies, s_Data.MaxIndicies);

		s_Data.RendererShader = new Shader("./shaders/Cube_VP.glsl", "./shaders/Cube_FP.glsl");
		s_Data.RendererShader->SetUniformSampler2D("texture0", 0);
		s_Data.RendererShader->SetUniformSampler2D("texture1", 1);
		s_Data.RendererShader->SetUniformSampler2D("texture2", 2);
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
		//LOG_WARN("Standard Flushing");
		Flush();
	}

	void Renderer::Submit(float* meshData, uint32_t dataSize)
	{
		VertexData vertexData;

		if (s_Data.IndexCount >= s_Data.MaxIndicies)
		{
			// LOG_DEBUG("Premature Flushing ({:d})", s_Data.RendererVertexData.size());
			Flush();
		}

		for (uint32_t i = 0; i < dataSize / sizeof(float); i += sizeof(VertexData) / sizeof(float))
		{
			vertexData.Transform = glm::vec3(meshData[i],
			                                 meshData[i + 1],
			                                 meshData[i + 2]);

			vertexData.Color = glm::vec3(meshData[i + 3],
			                             meshData[i + 4],
			                             meshData[i + 5]);
			
			vertexData.TexCoords = glm::vec2(meshData[i + 6],
			                                 meshData[i + 7]);
			
			vertexData.TexIndex = meshData[i + 8];

			s_Data.RendererVertexData.push_back(vertexData);
		}

		s_Data.IndexCount += 36; /* I only know this because all I'm drawing right now is cubes */
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
		s_Data.RendererIndicies->Bind();
		s_Data.RendererVertexArray->Bind();

		glDrawElements(GL_TRIANGLES, s_Data.MaxIndicies, GL_UNSIGNED_INT, 0);
	}

}