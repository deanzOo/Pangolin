#pragma once

#include <glm/glm.hpp>

namespace GamEngine {
	class Shader {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* create(const std::string& vertex_src, const std::string& fragment_src);
	};
}