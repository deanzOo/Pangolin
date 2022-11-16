#include "TextureLayer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"
#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

TextureLayer::TextureLayer() 
	: Layer("Exmaple"), _camera_controller(1280.0f / 720.0f, true)
{
	_square_vertex_array = Pangolin::VertexArray::create();

	float square_vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	_square_vertex_buffer = Pangolin::VertexBuffer::create(square_vertices, sizeof(square_vertices));

	{
		Pangolin::BufferLayout square_layout = {
			{ Pangolin::ShaderDataType::Float3, "i_position"},
			{ Pangolin::ShaderDataType::Float2, "i_text_coord"}
		};
		_square_vertex_buffer->set_layout(square_layout);
	}
	_square_vertex_array->add_vertex_buffer(_square_vertex_buffer);

	uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };
	_square_index_buffer = Pangolin::IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));
	_square_vertex_array->set_index_buffer(_square_index_buffer);

	_square_vertex_array->unbind();

	_texture_shader = Pangolin::Shader::create("assets/shaders/texture/");

	_texture = Pangolin::Texture2D::create("assets/textures/PL.png");

	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_texture_shader)->bind();
	std::dynamic_pointer_cast<Pangolin::OpenGLShader>(_texture_shader)->upload_uniform_int("u_texture", 0);
}

void TextureLayer::on_update(Pangolin::Timestep step)
{
	_camera_controller.on_update(step);

	Pangolin::Renderer::begin_scene(_camera_controller.get_camera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), _square_pos);

	_texture->bind();
	Pangolin::Renderer::submit(_texture_shader, _square_vertex_array, translation * scale);

	Pangolin::Renderer::end_scene();
}

void TextureLayer::on_event(Pangolin::Event& event) {
	_camera_controller.on_event(event);
}
