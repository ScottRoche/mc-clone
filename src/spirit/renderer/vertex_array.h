#pragma once

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

		void AddVertexBuffer(VertexBuffer* vertexBuffer);

	private:
		unsigned int m_Array;
		unsigned int m_AttributeIndex;

		VertexBuffer* m_VertexBuffer;
	};
}