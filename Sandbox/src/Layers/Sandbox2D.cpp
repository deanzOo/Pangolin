#include "gepch.h"
#include "Sandbox2D.h"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

Sandbox2D::Sandbox2D(): Pangolin::Layer("Sandbox2D"), _camera_controller(1280.0f / 720.0f, true)
{
}

void Sandbox2D::on_attach()
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

	uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };
	_square_index_buffer = Pangolin::IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));
	_square_vertex_array->set_index_buffer(_square_index_buffer);

	_square_vertex_array->unbind();

	_flat_color_shader = Pangolin::Shader::create("assets/shaders/flat_color/");
}

void Sandbox2D::on_detach()
{
}

void Sandbox2D::on_update(Pangolin::Timestep step)
{
	_camera_controller.on_update(step);

	Pangolin::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
	Pangolin::RenderCommand::clear();

	Pangolin::Renderer::begin_scene(_camera_controller.get_camera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_flat_color_shader)->bind();
	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_flat_color_shader)->upload_uniform_float3("u_color", _square_color);

	Pangolin::Renderer::submit(_flat_color_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Pangolin::Renderer::end_scene();
}

void Sandbox2D::on_imgui_render()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Square Color", glm::value_ptr(_square_color));
	float pos[3] = { _square_pos.x, _square_pos.y, _square_pos.z };
	ImGui::InputFloat3("Square Pos", pos, NULL, NULL);
	_square_pos = { pos[0], pos[1], pos[2] };

	ImGui::End();
}

void Sandbox2D::on_event(Pangolin::Event& event)
{
	_camera_controller.on_event(event);
}
