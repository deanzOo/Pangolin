#include "gepch.h"
#include "Renderer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

namespace GamEngine {

	Renderer::SceneData* Renderer::_scene_data = new Renderer::SceneData;

	void Renderer::init() {
		RenderCommand::init();
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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->upload_uniform_mat4("u_view_projection", _scene_data->view_projection_matrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->upload_uniform_mat4("u_transform", transform);

		vertex_array->bind();
		RenderCommand::draw_indexed(vertex_array);
	}
}