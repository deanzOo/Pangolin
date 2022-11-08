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

		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t _renderer_id;
	};
}