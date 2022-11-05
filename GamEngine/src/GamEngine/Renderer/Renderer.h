#pragma once

namespace GamEngine {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		Max = OpenGL
	};


	class Renderer {
	public:
		inline static RendererAPI get_api() { return s_renderer_api; }
		inline static RendererAPI set_api(RendererAPI api) { GE_CORE_ASSERT(api < RendererAPI::Max, "Invalid api!"); s_renderer_api = api; }
	private:
		static RendererAPI s_renderer_api;
	};

}