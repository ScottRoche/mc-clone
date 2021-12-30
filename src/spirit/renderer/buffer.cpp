#include "buffer.h"

#include "core/log.h"

namespace Spirit
{

/*****************************************************************************
 * Vertex Buffer
*****************************************************************************/

	VertexBuffer::VertexBuffer(uint32_t size)
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(float* verticies, uint32_t size)
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_BufferId);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetLayout(std::initializer_list<BufferElement> bufferLayout)
	{
		m_Layout = BufferLayout(bufferLayout);

		LOG_DEBUG("---[ Vertex Buffer Layout ]---");

		#define TO_STRING(_str, _type) _str = #_type // Just for temporary use. Shouldn't exist.
		for (BufferElement element : m_Layout.GetElements())
		{
			std::string typeString;

			switch(element.Type)
			{
				case ElementType::Float: TO_STRING(typeString, ElementType::Float); break;
				default: typeString = "None"; break;
			};

			LOG_DEBUG("Size: {:d}, Type: {:s}, Normalized: {:s}, Offset: 0x{:08x}",
			          element.Size,
			          typeString,
			          element.Normalized ? "True" : "False",
			          (unsigned int)(uintptr_t)element.Offset);
		}
		#undef TO_STRING
	}

	void VertexBuffer::AddData(float* vertexData, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertexData);
		m_BufferEnd += size;
	}

/*****************************************************************************
 * Index Buffer
*****************************************************************************/

	IndexBuffer::IndexBuffer(uint32_t* indicies, uint32_t size)
	{
		glGenBuffers(1, &m_BufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferId);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}