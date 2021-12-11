#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Spirit
{
	enum class ElementType
	{
		NONE = 0, Float /* More to come */
	};

	struct BufferElement
	{
		uint32_t Size;
		ElementType Type;
		bool Normalized;
		void* Offset;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement> elements)
		{
			for (BufferElement element : elements)
			{
				m_Stride += 4 * element.Size; // This is pretty horrible.
				m_Elements.push_back(element);
			}
		}

		std::vector<BufferElement>& GetElements() { return m_Elements; }
		uint32_t GetStride() const { return m_Stride; }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* verticies, uint32_t size);
		~VertexBuffer();

		void Bind();
		void Unbind();

		void SetLayout(std::initializer_list<BufferElement> bufferLayout);
	
		BufferLayout& GetLayout() { return m_Layout; }

		void AddData(float* vertexData, uint32_t size);

	private:
		unsigned int m_BufferId;
		unsigned int m_BufferEnd = 0;

		BufferLayout m_Layout;
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