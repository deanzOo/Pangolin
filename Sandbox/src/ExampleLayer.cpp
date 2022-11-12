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
	: Layer("Exmaple"), _camera(-1.6f, 1.6f, -0.9f, 0.9f)
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

	std::string flat_color_vertex_src = R"(
			#version 330 core

			layout(location = 0) in vec3 i_position;

			uniform mat4 u_view_projection;
			uniform mat4 u_transform;

			void main() {
				gl_Position = u_view_projection * u_transform * vec4(i_position, 1.0);
			}
		)";

	std::string flat_color_fragment_src = R"(
			#version 330 core

			layout(location = 0) out vec4 o_color;

			uniform vec3 u_color;

			void main() {
				o_color = vec4(u_color, 1.0);
			}
		)";

	_flat_color_shader.reset(GamEngine::Shader::create(flat_color_vertex_src, flat_color_fragment_src));


	std::string texture_vertex_src = R"(
			#version 330 core

			layout(location = 0) in vec3 i_position;
			layout(location = 1) in vec2 i_texture;

			uniform mat4 u_view_projection;
			uniform mat4 u_transform;

			out vec2 v_texture_coord;

			void main() {
				v_texture_coord = i_texture;
				gl_Position = u_view_projection * u_transform * vec4(i_position, 1.0);
			}
		)";

	std::string texture_fragment_src = R"(
			#version 330 core

			layout(location = 0) out vec4 o_color;

			in vec2 v_texture_coord;

			uniform sampler2D u_texture;

			void main() {
				o_color = texture(u_texture, v_texture_coord);
			}
		)";

	_texture_shader.reset(GamEngine::Shader::create(texture_vertex_src, texture_fragment_src));

	_texture = GamEngine::Texture2D::create("assets/textures/example.png");

	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_texture_shader)->bind();
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_texture_shader)->upload_uniform_int("u_texture", 0);
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

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_flat_color_shader)->bind();
	std::dynamic_pointer_cast<GamEngine::OpenGLShader>(_flat_color_shader)->upload_uniform_float3("u_color", _square_color);

	for (int y = 5;  y < 25; y++) {
		for (int x = 5; x < 25; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			GamEngine::Renderer::submit(_flat_color_shader, _square_vertex_array, transform);
		}
	}

	_texture->bind();
	
	GamEngine::Renderer::submit(_texture_shader, _square_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
