#include "plpch.h"
#include "OpenGLTexture2D.h"

#include "stb_image.h"

namespace Pangolin {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path): _path(path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* image_data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PL_CORE_ASSERT(image_data, "Failed to load image!");

		_width = width;
		_height = height;

		_internal_format = 0;
		_data_format = 0;
		if (channels == 4) {
			_internal_format = GL_RGBA8;
			_data_format = GL_RGBA;
		}
		else if (channels == 3) {
			_internal_format = GL_RGB8;
			_data_format = GL_RGB;
		}

		PL_CORE_ASSERT(_internal_format & _data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, _internal_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, _data_format, GL_UNSIGNED_BYTE, image_data);

		stbi_image_free(image_data);
	}
	
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : _width(width), _height(height)
	{
		_internal_format = GL_RGBA8;
		_data_format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, _internal_format, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_renderer_id);
	}

	void OpenGLTexture2D::set_data(void* data, uint32_t size)
	{
		uint32_t bytes_per_pixel = _data_format == GL_RGBA ? 4 : 3;
		PL_CORE_ASSERT(size == _width * _height * bytes_per_pixel, "Data has to be the size of the entire Texture");
		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, _data_format, GL_UNSIGNED_BYTE, data);
	}
	
	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, _renderer_id);
	}
}