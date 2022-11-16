#include "plpch.h"
#include "Renderer2D.h"
#include "Arrays/VertexArray.h"
#include "RenderCommand.h"
#include "Shaders/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pangolin {

	struct Renderer2DStorage {
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> flat_color_shader;
	};

	static Renderer2DStorage* _storage;

	void Renderer2D::init()
	{
		_storage = new Renderer2DStorage();

		_storage->quad_vertex_array = VertexArray::create();

		float quad_vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> vertex_buffer = VertexBuffer::create(quad_vertices, sizeof(quad_vertices));

		vertex_buffer->set_layout({
			{ ShaderDataType::Float3, "i_position"}
		});
		_storage->quad_vertex_array->add_vertex_buffer(vertex_buffer);

		uint32_t quad_indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> index_buffer = IndexBuffer::create(quad_indices, sizeof(quad_indices) / sizeof(uint32_t));
		_storage->quad_vertex_array->set_index_buffer(index_buffer);

		_storage->quad_vertex_array->unbind();

		_storage->flat_color_shader = Shader::create("assets/shaders/flat_color/");
	}
	
	void Renderer2D::shutdown()
	{
		delete _storage;
	}
	
	void Renderer2D::begin_scene(OrthographicCamera& camera)
	{
		_storage->flat_color_shader->bind();
		_storage->flat_color_shader->set_uniform_mat4("u_view_projection", camera.get_view_projection_matrix());
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
		_storage->flat_color_shader->bind();
		_storage->flat_color_shader->set_uniform_float4("u_color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		_storage->flat_color_shader->set_uniform_mat4("u_transform", transform);

		_storage->quad_vertex_array->bind();
		RenderCommand::draw_indexed(_storage->quad_vertex_array);
	}
}