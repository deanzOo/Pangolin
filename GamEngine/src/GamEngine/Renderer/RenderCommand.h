#pragma once

#include "RendererAPI.h"

namespace GamEngine {
	class RenderCommand {
	public:
		inline static void set_clear_color(const glm::vec4& color) { renderer_api->set_clear_color(color); };
		inline static void clear() { renderer_api->clear(); };

		inline static void draw_indexed(const Ref<VertexArray>& vertex_array) { renderer_api->draw_indexed(vertex_array); }
	private:
		static RendererAPI* renderer_api;
	};
}