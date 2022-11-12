#pragma once

#include "GamEngine/Renderer/Shaders/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace GamEngine {
	class OpenGLShader : public Shader {
	public:
	public:
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		void upload_uniform_int(const std::string& name, int value);

		void upload_uniform_float(const std::string& name, float value);
		void upload_uniform_float2(const std::string& name, const glm::vec2& values);
		void upload_uniform_float3(const std::string& name, const glm::vec3& values);
		void upload_uniform_float4(const std::string& name, const glm::vec4& values);

		void upload_uniform_mat3(const std::string& name, const glm::mat3& matrix);
		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string read_file(const std::string& filepath);
		std::unordered_map<GLenum, std::string> load_from_path(const std::string& path);
	private:
		uint32_t _renderer_id;
	};
}