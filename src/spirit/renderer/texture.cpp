#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "core/log.h"

namespace Spirit
{
	Texture::Texture(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (data == nullptr)
		{
			LOG_ERROR("Failed to load image texture ({:s})", path);
			return;
		}

		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureId);
	}

	void Texture::Bind(uint32_t slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}