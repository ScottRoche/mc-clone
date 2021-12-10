#pragma once

#include <memory>

#include "buffer.h"

namespace Spirit
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer);

	private:
		unsigned int m_Array;
		unsigned int m_AttributeCount;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}