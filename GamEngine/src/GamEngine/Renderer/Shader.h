#pragma once

#include <string>

namespace GamEngine {
	class Shader {
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void bind() const;
		void unbind() const;
	private:
		uint32_t m_renderer_id;
	};
}