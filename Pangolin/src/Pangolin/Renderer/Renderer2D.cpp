#include "plpch.h"
#include "Renderer2D.h"
#include "Arrays/VertexArray.h"
#include "RenderCommand.h"
#include "Shaders/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pangolin {

	struct Renderer2DStorage {
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;
	};

	static Renderer2DStorage* _storage;

	void Renderer2D::init()
	{
		_storage = new Renderer2DStorage();

		_storage->quad_vertex_array = VertexArray::create();

		float quad_vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> vertex_buffer = VertexBuffer::create(quad_vertices, sizeof(quad_vertices));

		vertex_buffer->set_layout({
			{ ShaderDataType::Float3, "i_position"},
			{ ShaderDataType::Float2, "i_texture"}
		});
		_storage->quad_vertex_array->add_vertex_buffer(vertex_buffer);

		uint32_t quad_indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> index_buffer = IndexBuffer::create(quad_indices, sizeof(quad_indices) / sizeof(uint32_t));
		_storage->quad_vertex_array->set_index_buffer(index_buffer);

		_storage->white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		_storage->white_texture->set_data(&white_texture_data, sizeof(uint32_t));

		_storage->quad_vertex_array->unbind();

		_storage->texture_shader = Shader::create("assets/shaders/texture/");
		_storage->texture_shader->bind();
		_storage->texture_shader->set_uniform_int("u_texture", 0);
	}
	
	void Renderer2D::shutdown()
	{
		delete _storage;
	}
	
	void Renderer2D::begin_scene(OrthographicCamera& camera)
	{
		_storage->texture_shader->bind();
		_storage->texture_shader->set_uniform_mat4("u_view_projection", camera.get_view_projection_matrix());
	}
	
	void Renderer2D::end_scene()
	{

	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}
	
	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		_storage->texture_shader->set_uniform_float4("u_color", color);
		_storage->white_texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		_storage->texture_shader->set_uniform_mat4("u_transform", transform);

		_storage->quad_vertex_array->bind();
		RenderCommand::draw_indexed(_storage->quad_vertex_array);
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		_storage->texture_shader->set_uniform_float4("u_color", glm::vec4(1.0f));
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		_storage->texture_shader->set_uniform_mat4("u_transform", transform);

		_storage->quad_vertex_array->bind();
		RenderCommand::draw_indexed(_storage->quad_vertex_array);
	}
}