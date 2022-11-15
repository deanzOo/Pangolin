#pragma once

#include "Pangolin/Renderer/Textures/Texture2D.h"

namespace Pangolin {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		inline virtual uint32_t get_width() const override { return _width; };
		inline virtual uint32_t get_height() const override { return _height; };

		virtual void bind(uint32_t slot = 0) const override;
	private:
		std::string _path;
		uint32_t _width;
		uint32_t _height;

		uint32_t _renderer_id;
	};
}