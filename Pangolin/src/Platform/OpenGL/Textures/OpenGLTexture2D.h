#pragma once

#include "Pangolin/Renderer/Textures/Texture2D.h"
#include <glad/glad.h>

namespace Pangolin {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		inline virtual uint32_t get_width() const override { return _width; };
		inline virtual uint32_t get_height() const override { return _height; };
		inline virtual uint32_t get_renderer_id() const override { return _renderer_id; }

		void set_data(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;

		inline virtual bool equals(const Texture2D& other) const override { return _renderer_id == ((OpenGLTexture2D&)other)._renderer_id; }
	private:
		std::string _path;
		uint32_t _width, _height;

		uint32_t _renderer_id;

		GLenum _internal_format, _data_format;
	};
}