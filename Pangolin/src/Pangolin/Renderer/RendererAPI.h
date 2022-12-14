#pragma once

#include "glm/glm.hpp"
#include "Arrays/VertexArray.h"

namespace Pangolin {
	class RendererAPI {
	public:
		enum class API {
			None = 0, OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void init() = 0;
		virtual void set_clear_color(const glm::vec4& color) = 0;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void clear() = 0;

		virtual void draw_indexed(const Ref<VertexArray>& vertex_array, uint32_t count = 0) = 0;

		inline static API get_api() { return s_API; }
	private:
		static API s_API;
	};
}