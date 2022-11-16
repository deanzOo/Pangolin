#include "TilemapLayer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

TilemapLayer::TilemapLayer()
	: Layer("Exmaple"), _camera_controller(1280.0f / 720.0f, true)
{
	_square_vertex_array = Pangolin::VertexArray::create();

	float square_vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	_square_vertex_buffer = Pangolin::VertexBuffer::create(square_vertices, sizeof(square_vertices));

	{
		Pangolin::BufferLayout square_layout = {
			{ Pangolin::ShaderDataType::Float3, "i_position"}
		};
		_square_vertex_buffer->set_layout(square_layout);
	}
	_square_vertex_array->add_vertex_buffer(_square_vertex_buffer);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	_square_index_buffer = Pangolin::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
	_square_vertex_array->set_index_buffer(_square_index_buffer);

	_square_vertex_array->unbind();

	_flat_color_shader = Pangolin::Shader::create("assets/shaders/flat_color/");
}

void TilemapLayer::on_update(Pangolin::Timestep step)
{
	_camera_controller.on_update(step);

	Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
	Pangolin::RenderCommand::clear();

	Pangolin::Renderer::begin_scene(_camera_controller.get_camera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_flat_color_shader)->bind();
	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_flat_color_shader)->opengl_set_uniform_float3("u_color", _square_color);

	for (int y = 10; y < 30; y++) {
		for (int x = 10; x < 30; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Pangolin::Renderer::submit(_flat_color_shader, _square_vertex_array, transform);
		}
	}

	Pangolin::Renderer::end_scene();
}

void TilemapLayer::on_imgui_render()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Tilemap Color", glm::value_ptr(_square_color));

	ImGui::End();
}

void TilemapLayer::on_event(Pangolin::Event& event) {
	_camera_controller.on_event(event);
}
