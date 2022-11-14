#include "ExampleLayer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include <GamEngine/Renderer/Renderer.h>
#include <GamEngine/Core/KeyCodes.h>
#include <GamEngine/Events/Event.h>
#include <GamEngine/Core/Input.h>
#include "glm/gtc/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

ExampleLayer::ExampleLayer() 
	: Layer("Exmaple"), _camera_controller(1280.0f / 720.0f, true)
{
	_square_vertex_array.reset(GamEngine::VertexArray::create());

	float square_vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	_square_vertex_buffer.reset(GamEngine::VertexBuffer::create(square_vertices, sizeof(square_vertices)));

	{
		GamEngine::BufferLayout square_layout = {
			{ GamEngine::ShaderDataType::Float3, "i_position"},
			{ GamEngine::ShaderDataType::Float2, "i_text_coord"}
		};
		_square_vertex_buffer->set_layout(square_layout);
	}
	_square_vertex_array->add_vertex_buffer(_square_vertex_buffer);

	uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };
	_square_index_buffer.reset(GamEngine::IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
	_square_vertex_array->set_index_buffer(_square_index_buffer);

	_square_vertex_array->unbind();

	auto flat_color_shader = _shader_library.load("assets/shaders/flat_color/");
	auto texture_shader = _shader_library.load("assets/shaders/texture/");

	_texture = GamEngine::Texture2D::create("assets/textures/example.png");

	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(texture_shader)->bind();
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(texture_shader)->upload_uniform_int("u_texture", 0);
}

void ExampleLayer::on_update(GamEngine::Timestep step)
{
	_camera_controller.on_update(step);

	GamEngine::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
	GamEngine::RenderCommand::clear();

	GamEngine::Renderer::begin_scene(_camera_controller.get_camera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto flat_color_shader = _shader_library.get("flat_color");

	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(flat_color_shader)->bind();
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(flat_color_shader)->upload_uniform_float3("u_color", _square_color);

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			GamEngine::Renderer::submit(flat_color_shader, _square_vertex_array, transform);
		}
	}

	auto texture_shader = _shader_library.get("texture");

	GamEngine::Renderer::submit(flat_color_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	_texture->bind();
	GamEngine::Renderer::submit(texture_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	GamEngine::Renderer::end_scene();
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Square Color", glm::value_ptr(_square_color));

	ImGui::End();
}

void ExampleLayer::on_event(GamEngine::Event& event) {
	_camera_controller.on_event(event);
}
