#include "vertex_array.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Spirit
{
	static GLenum GetShaderType(ElementType type)
	{
		switch (type)
		{
			case ElementType::Float:    return GL_FLOAT;
			default:                    return 0;
		}
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_Array);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_Array);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_Array);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer)
	{
		BufferLayout& bufferLayout = vertexBuffer.GetLayout();
		for (BufferElement element : bufferLayout.GetElements())
		{
			glVertexAttribPointer(m_AttributeCount,
			                      element.Size,
			                      GetShaderType(element.Type),
			                      element.Normalized ? GL_TRUE : GL_FALSE,
			                      bufferLayout.GetStride(),
			                      element.Offset);
			glEnableVertexAttribArray(m_AttributeCount);
			m_AttributeCount++;
		}
	}
}
