#pragma once

#include <engine/sprtpch.h>

namespace Spirit
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot = 0);
		void Unbind();

	private:
		std::string path;

		uint32_t m_Width;
		uint32_t m_Height;

		unsigned int m_TextureId;
	};
}