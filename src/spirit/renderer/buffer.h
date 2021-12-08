#pragma once

#include <cstdint>

namespace Spirit
{
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size, float* verticies);
		~VertexBuffer();

		void Bind();
		void Unbind();

	private:
		unsigned int m_BufferId;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t size, uint32_t* indicies);
		~IndexBuffer();

		void Bind();
		void Unbind();

	private:
		unsigned int m_BufferId;
	};
}