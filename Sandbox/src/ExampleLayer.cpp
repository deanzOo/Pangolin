#include "ExampleLayer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include <GamEngine/Renderer/Renderer.h>
#include <GamEngine/Core/KeyCodes.h>
#include <GamEngine/Events/Event.h>
#include <GamEngine/Core/Input.h>
#include "glm/gtc/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

ExampleLayer::ExampleLayer() : Layer("Exmaple"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _square_position(0.0f) {

	_triangle_vertex_array.reset(GamEngine::VertexArray::create());

	float verticesTriangle[3 * 3] = {
		-0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f,
		0.0f, 0.5f, 1.0f
	};
	_triangle_vertex_buffer.reset(GamEngine::VertexBuffer::create(verticesTriangle, sizeof(verticesTriangle)));

	{
		GamEngine::BufferLayout layout_triangle = {
			{ GamEngine::ShaderDataType::Float3, "i_position"}
		};
		_triangle_vertex_buffer->set_layout(layout_triangle);
	}
	_triangle_vertex_array->add_vertex_buffer(_triangle_vertex_buffer);

	uint32_t indicesTriangle[3] = { 0, 1, 2 };
	_triangle_index_buffer.reset(GamEngine::IndexBuffer::create(indicesTriangle, sizeof(indicesTriangle) / sizeof(uint32_t)));
	_triangle_vertex_array->set_index_buffer(_triangle_index_buffer);

	_triangle_vertex_array->unbind();


	_square_vertex_array.reset(GamEngine::VertexArray::create());

	float verticesSquare[3 * 4] = {
		-0.2f, -0.2f, 0.0f,
		-0.2f, 0.2f, 0.0f,
		0.2f, 0.2f, 0.0f,
		0.2f, -0.2f, 0.0f
	};
	_square_vertex_buffer.reset(GamEngine::VertexBuffer::create(verticesSquare, sizeof(verticesSquare)));

	{
		GamEngine::BufferLayout layoutSquare = {
			{ GamEngine::ShaderDataType::Float3, "i_position"}
		};
		_square_vertex_buffer->set_layout(layoutSquare);
	}
	_square_vertex_array->add_vertex_buffer(_square_vertex_buffer);

	uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };
	_square_index_buffer.reset(GamEngine::IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
	_square_vertex_array->set_index_buffer(_square_index_buffer);

	_square_vertex_array->unbind();

	std::string vertex_src = R"(
			#version 330 core

			layout(location = 0) in vec3 i_position;

			uniform mat4 u_view_projection;
			uniform mat4 u_transform;

			void main() {
				gl_Position = u_view_projection * u_transform * vec4(i_position, 1.0);
			}
		)";

	std::string fragment_src = R"(
			#version 330 core

			layout(location = 0) out vec4 o_color;

			uniform vec3 u_color;

			void main() {
				o_color = vec4(u_color, 1.0);
			}
		)";

	_flat_color_shader.reset(GamEngine::Shader::create(vertex_src, fragment_src));
}

void ExampleLayer::on_attach()
{
	_flat_color_shader->bind();
}

void ExampleLayer::on_detach()
{
	_flat_color_shader->unbind();
}

void ExampleLayer::on_update(GamEngine::Timestep step)
{
	// GE_CLIENT_TRACE("Delta time: {0}s ({1}ms)", step.get_seconds(), step.get_milliseconds());
	
	float _timed_camera_move_spd = _camera_move_spd * step;
	float _timed_camera_rotate_spd = _camera_rotate_spd * step;
	glm::vec3 new_camera_position = _camera.get_position();
	float new_camera_rotation = _camera.get_rotation();
	if (GamEngine::Input::is_key_pressed(GE_KEY_W)) new_camera_position.y -= _timed_camera_move_spd;
	else if (GamEngine::Input::is_key_pressed(GE_KEY_A)) new_camera_position.x += _timed_camera_move_spd;
	else if (GamEngine::Input::is_key_pressed(GE_KEY_S)) new_camera_position.y += _timed_camera_move_spd;
	else if (GamEngine::Input::is_key_pressed(GE_KEY_D)) new_camera_position.x -= _timed_camera_move_spd;
	else if (GamEngine::Input::is_key_pressed(GE_KEY_UP)) new_camera_rotation += _timed_camera_rotate_spd;
	else if (GamEngine::Input::is_key_pressed(GE_KEY_DOWN)) new_camera_rotation -= _timed_camera_rotate_spd;
	_camera.set_position(new_camera_position);
	_camera.set_rotation(new_camera_rotation);

	GamEngine::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });
	GamEngine::RenderCommand::clear();

	GamEngine::Renderer::begin_scene(_camera);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

	/*
	* * * Example future API to render materials
	* 
	* GamEngine::MaterialRef material = new GamEngine::Material(_flat_color_shader);
	* GamEngine::MaterialInstanceRef material_instance = new GamEngine::MaterialInstance(material);
	* 
	* material_instance->set_value("u_color", red);
	* material_instance->set_texture("u_texture_map", texture);
	* sqaure_mash->set_material(material_instance);
	*/
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_flat_color_shader)->bind();
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_flat_color_shader)->upload_uniform_float3("u_color", _square_color);

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			GamEngine::Renderer::submit(_flat_color_shader, _square_vertex_array, transform);
		}
	}

	glm::vec4 green(0.2f, 0.8f, 0.3f, 1.0f);
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_flat_color_shader)->upload_uniform_float4("u_color", green);
	GamEngine::Renderer::submit(_flat_color_shader, _triangle_vertex_array);

	GamEngine::Renderer::end_scene();
}

void ExampleLayer::on_imgui_render()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Square Color", glm::value_ptr(_square_color));

	ImGui::End();
}

void ExampleLayer::on_event(GamEngine::Event& event) {
	GamEngine::EventDispatcher dispatcher(event);
	dispatcher.dispatch<GamEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(ExampleLayer::on_key_pressed));
}

bool ExampleLayer::on_key_pressed(GamEngine::KeyPressedEvent& event)
{
	GE_CLIENT_TRACE("{0}", (char)event.get_keycode());
	return false;
}
