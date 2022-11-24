#pragma once

#include "Pangolin/Renderer/Shaders/Shader.h"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Pangolin {
	struct ShaderComponents {
		std::string name;
		std::string src;
	};
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& path);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const std::string& get_name() const override { return _name; };

		virtual void set_uniform_int(const std::string& name, int value) override;
		virtual void set_uniform_int_array(const std::string& name, int* values, uint32_t count) override;
		virtual void set_uniform_mat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void set_uniform_float(const std::string& name, float value) override;
		virtual void set_uniform_float3(const std::string& name, const glm::vec3& values) override;
		virtual void set_uniform_float4(const std::string& name, const glm::vec4& values) override;

		void opengl_set_uniform_int(const std::string& name, int value);
		void opengl_set_uniform_int_array(const std::string& name, int* values, uint32_t count);
		void opengl_set_uniform_float(const std::string& name, float value);
		void opengl_set_uniform_float2(const std::string& name, const glm::vec2& values);
		void opengl_set_uniform_float3(const std::string& name, const glm::vec3& values);
		void opengl_set_uniform_float4(const std::string& name, const glm::vec4& values);

		void opengl_set_uniform_mat3(const std::string& name, const glm::mat3& matrix);
		void opengl_set_uniform_mat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string read_file(const std::string& filepath);
		std::unordered_map<GLenum, ShaderComponents> load_from_path(const std::string& path);
	private:
		uint32_t _renderer_id;
		std::string _name;
	};

}