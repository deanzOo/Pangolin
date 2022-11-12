#include "gepch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace GamEngine {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path): _path(path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* image_data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		GE_CORE_ASSERT(image_data, "Failed to load image!");

		_width = width;
		_height = height;

		uint32_t format = GL_RGB;
		if (channels == 4) format = GL_RGBA;

		uint32_t storage_format = GL_RGB8;
		if (channels == 4) storage_format = GL_RGBA8;

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, storage_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, format, GL_UNSIGNED_BYTE, image_data);

		stbi_image_free(image_data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_renderer_id);
	}
	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, _renderer_id);
	}
}