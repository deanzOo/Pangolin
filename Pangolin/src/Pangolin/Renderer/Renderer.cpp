#include "plpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Pangolin {

	Renderer::SceneData* Renderer::_scene_data = new Renderer::SceneData;

	void Renderer::init() {
		PL_PROFILE_FUNCTION();
		
		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::shutdown()
	{
		Renderer2D::shutdown();
	}

	void Renderer::on_window_resize(uint32_t width, uint32_t height) {
		RenderCommand::set_viewport(0, 0, width, height);
	}

	void Renderer::begin_scene(OrthographicCamera& camera)
	{
		_scene_data->view_projection_matrix = camera.get_view_projection_matrix();
	}
	void Renderer::end_scene()
	{
	}
	void Renderer::submit(const Ref<Shader> shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->bind();
		shader->set_uniform_mat4("u_view_projection", _scene_data->view_projection_matrix);
		shader->set_uniform_mat4("u_transform", transform);

		vertex_array->bind();
		RenderCommand::draw_indexed(vertex_array);
	}
}