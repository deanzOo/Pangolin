#pragma once

#include <glm/glm.hpp>

namespace Pangolin {
	class Shader {
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& get_name() const = 0;

		virtual void set_uniform_int(const std::string& name, const int value) = 0;
		virtual void set_uniform_float3(const std::string& name, const glm::vec3& values) = 0;
		virtual void set_uniform_float4(const std::string& name, const glm::vec4& values) = 0;
		virtual void set_uniform_mat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Ref<Shader> create(const std::string& path);
		static Ref<Shader> create(const std::string& name, const std::string& path);
	};
}