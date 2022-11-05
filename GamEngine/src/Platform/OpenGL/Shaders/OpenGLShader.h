#pragma once

#include "GamEngine/Renderer/Shaders/Shader.h"

namespace GamEngine {
	class OpenGLShader : public Shader {
	public:
	public:
		OpenGLShader(const std::string& vertex_src, const std::string& fragment_src);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		uint32_t m_renderer_id;
	};
}