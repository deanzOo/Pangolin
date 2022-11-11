#pragma once

#include "RenderCommand.h"
#include "Shaders/Shader.h"
#include "OrthographicCamera.h"

namespace GamEngine {

	class Renderer {
	public:
		static void begin_scene(OrthographicCamera& camera);
		static void end_scene();

		static void submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API get_api() { return RendererAPI::get_api(); }
	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
		};

		static SceneData* _scene_data;
	};

}