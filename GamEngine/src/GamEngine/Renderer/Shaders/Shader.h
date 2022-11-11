#pragma once

namespace GamEngine {
	class Shader {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* create(const std::string& vertex_src, const std::string& fragment_src);
	};
}