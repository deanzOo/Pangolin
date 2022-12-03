#include "plpch.h"
#include "Renderer2D.h"
#include "Arrays/VertexArray.h"
#include "RenderCommand.h"
#include "Shaders/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pangolin {

	struct QuadVertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texture_coordinates;
		float texture_index;
		float tile_factor;
	};

	struct Renderer2DStorage {
		static const uint32_t VERTICES_PER_QUAD = 4;
		static const uint32_t INDICES_PER_QUAD = 6;

		static const uint32_t MAX_QUADS = 20000;
		static const uint32_t MAX_VERTICES = MAX_QUADS * VERTICES_PER_QUAD;
		static const uint32_t MAX_INDICES = MAX_QUADS * INDICES_PER_QUAD;
		static const uint32_t MAX_TEXTURE_SLOTS = 32;

		const float WHITE_TEXTURE_INDEX = 0.0f;

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;

		QuadVertex* quad_vertex_buffer_base = nullptr;
		QuadVertex* quad_vertex_buffer_ptr = nullptr;

		uint32_t quad_indices_count = 0;

		std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> texture_slots;
		uint32_t texture_slot_index = 1; // 0 belongs to white texture
		glm::vec4 quad_vertex_positions[4];

		Renderer2D::statistics stats;
	};

	static Renderer2DStorage _storage;

	void Renderer2D::init()
	{
		PL_PROFILE_FUNCTION();

		_storage.quad_vertex_array = VertexArray::create();

		_storage.quad_vertex_buffer = VertexBuffer::create(sizeof(QuadVertex) * Renderer2DStorage::MAX_INDICES);

		_storage.quad_vertex_buffer->set_layout({
			{ ShaderDataType::Float3, "i_position"},
			{ ShaderDataType::Float4, "i_color"},
			{ ShaderDataType::Float2, "i_texture_coordinate"},
			{ ShaderDataType::Float, "i_texture_index"},
			{ ShaderDataType::Float, "i_tile_factor"}
		});
		_storage.quad_vertex_array->add_vertex_buffer(_storage.quad_vertex_buffer);

		_storage.quad_vertex_buffer_base = new QuadVertex[Renderer2DStorage::MAX_VERTICES];

		uint32_t* quad_indices = new uint32_t[Renderer2DStorage::MAX_INDICES];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < Renderer2DStorage::MAX_INDICES; i += Renderer2DStorage::INDICES_PER_QUAD) {
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;
			
			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> index_buffer = IndexBuffer::create(quad_indices, Renderer2DStorage::MAX_INDICES);
		_storage.quad_vertex_array->set_index_buffer(index_buffer);
		delete[] quad_indices;

		_storage.white_texture = Texture2D::create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		_storage.white_texture->set_data(&white_texture_data, sizeof(uint32_t));

		int32_t samplers[Renderer2DStorage::MAX_TEXTURE_SLOTS];
		for (uint32_t i = 0; i < Renderer2DStorage::MAX_TEXTURE_SLOTS; i++)
			samplers[i] = i;

		_storage.texture_shader = Shader::create("assets/shaders/texture/");
		_storage.texture_shader->bind();
		_storage.texture_shader->set_uniform_int_array("u_textures", samplers, Renderer2DStorage::MAX_TEXTURE_SLOTS);;

		_storage.texture_slots[0] = _storage.white_texture;

		_storage.quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		_storage.quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
		_storage.quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
		_storage.quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
	}
	
	void Renderer2D::shutdown()
	{
		PL_PROFILE_FUNCTION();
	}
	
	void Renderer2D::begin_scene(OrthographicCamera& camera)
	{
		PL_PROFILE_FUNCTION();

		_storage.texture_shader->bind();
		_storage.texture_shader->set_uniform_mat4("u_view_projection", camera.get_view_projection_matrix());

		reset_quad_storage();
	}
	
	void Renderer2D::end_scene()
	{
		PL_PROFILE_FUNCTION();

		auto data_size = (uint8_t*)_storage.quad_vertex_buffer_ptr - (uint8_t*)_storage.quad_vertex_buffer_base;
		_storage.quad_vertex_buffer->set_data(_storage.quad_vertex_buffer_base, (uint32_t)data_size);

		flush();
	}

	void Renderer2D::flush()
	{
		PL_PROFILE_FUNCTION();

		for (uint32_t i = 0; i < _storage.texture_slot_index; i++)
			_storage.texture_slots[i]->bind(i);
		
		RenderCommand::draw_indexed(_storage.quad_vertex_array, _storage.quad_indices_count);

		_storage.stats.draw_calls++;
	}

	void Renderer2D::overflow_flush()
	{
		end_scene();
		reset_quad_storage();
	}

	void Renderer2D::reset_quad_storage()
	{
		_storage.quad_vertex_buffer_ptr = _storage.quad_vertex_buffer_base;
		_storage.quad_indices_count = 0;
		_storage.texture_slot_index = 1;

	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, color);
	}
	
	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		PL_PROFILE_FUNCTION();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[0];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(0.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[1];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 1.0f, 0.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[2];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(1.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[3];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 0.0f, 1.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tile_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, texture, tile_factor);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tile_factor, const glm::vec4& tint_color)
	{
		PL_PROFILE_FUNCTION();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float texture_index = 0.0f;

		for (uint32_t i = 0; i < _storage.texture_slot_index; i++) {
			if (_storage.texture_slots[i]->equals(*texture)) {
				texture_index = (float)i;
				break;
			}
		}

		if (texture_index == 0.0f) {
			texture_index = (float)_storage.texture_slot_index;
			_storage.texture_slots[_storage.texture_slot_index] = texture;
			_storage.texture_slot_index++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[0];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(0.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[1];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 1.0f, 0.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[2];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(1.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[3];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 0.0f, 1.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}

	void Renderer2D::draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D> sub_texture, float tile_factor, const glm::vec4& tint_color)
	{
		draw_quad({ position.x, position.y, 0.0f }, size, sub_texture, tile_factor, tint_color);
	}

	void Renderer2D::draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D> sub_texture, float tile_factor, const glm::vec4& tint_color)
	{
		PL_PROFILE_FUNCTION();

		const Ref<Texture2D> texture = sub_texture->get_texture();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		const glm::vec2* texture_coordinates = sub_texture->get_texture_coordinates();

		float texture_index = 0.0f;

		for (uint32_t i = 0; i < _storage.texture_slot_index; i++) {
			if (_storage.texture_slots[i]->equals(*texture)) {
				texture_index = (float)i;
				break;
			}
		}

		if (texture_index == 0.0f) {
			texture_index = (float)_storage.texture_slot_index;
			_storage.texture_slots[_storage.texture_slot_index] = texture;
			_storage.texture_slot_index++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		for (size_t i = 0; i < _storage.VERTICES_PER_QUAD; i++) {
			_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[i];
			_storage.quad_vertex_buffer_ptr->color = color;
			_storage.quad_vertex_buffer_ptr->texture_coordinates = texture_coordinates[i];
			_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
			_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
			_storage.quad_vertex_buffer_ptr++;
		}

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}

	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		PL_PROFILE_FUNCTION();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[0];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(0.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[1];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 1.0f, 0.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[2];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(1.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[3];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 0.0f, 1.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = _storage.WHITE_TEXTURE_INDEX;
		_storage.quad_vertex_buffer_ptr->tile_factor = 1.0f;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}

	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tile_factor, const glm::vec4& tint_color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tile_factor);
	}

	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tile_factor, const glm::vec4& tint_color)
	{
		PL_PROFILE_FUNCTION();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float texture_index = 0.0f;

		for (uint32_t i = 0; i < _storage.texture_slot_index; i++) {
			if (_storage.texture_slots[i]->equals(*texture)) {
				texture_index = (float)i;
				break;
			}
		}

		if (texture_index == 0.0f) {
			texture_index = (float)_storage.texture_slot_index;
			_storage.texture_slots[_storage.texture_slot_index] = texture;
			_storage.texture_slot_index++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[0];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(0.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[1];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 1.0f, 0.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[2];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = glm::vec2(1.0f);
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[3];
		_storage.quad_vertex_buffer_ptr->color = color;
		_storage.quad_vertex_buffer_ptr->texture_coordinates = { 0.0f, 1.0f };
		_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
		_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
		_storage.quad_vertex_buffer_ptr++;

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}
	
	void Renderer2D::draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D> texture, float tile_factor, const glm::vec4& tint_color)
	{
		draw_rotated_quad({ position.x, position.y, 0.0f }, size, rotation, texture, tile_factor, tint_color);
	}
	
	void Renderer2D::draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D> sub_texture, float tile_factor, const glm::vec4& tint_color)
	{
		PL_PROFILE_FUNCTION();

		const Ref<Texture2D> texture = sub_texture->get_texture();

		if (_storage.quad_indices_count >= Renderer2DStorage::MAX_INDICES)
			overflow_flush();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		const glm::vec2* texture_coordinates = sub_texture->get_texture_coordinates();

		float texture_index = 0.0f;

		for (uint32_t i = 0; i < _storage.texture_slot_index; i++) {
			if (_storage.texture_slots[i]->equals(*texture)) {
				texture_index = (float)i;
				break;
			}
		}

		if (texture_index == 0.0f) {
			texture_index = (float)_storage.texture_slot_index;
			_storage.texture_slots[_storage.texture_slot_index] = texture;
			_storage.texture_slot_index++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });


		for (size_t i = 0; i < _storage.VERTICES_PER_QUAD; i++) {
			_storage.quad_vertex_buffer_ptr->position = transform * _storage.quad_vertex_positions[i];
			_storage.quad_vertex_buffer_ptr->color = color;
			_storage.quad_vertex_buffer_ptr->texture_coordinates = texture_coordinates[i];
			_storage.quad_vertex_buffer_ptr->texture_index = texture_index;
			_storage.quad_vertex_buffer_ptr->tile_factor = tile_factor;
			_storage.quad_vertex_buffer_ptr++;
		}

		_storage.quad_indices_count += Renderer2DStorage::INDICES_PER_QUAD;

		_storage.stats.quad_count++;
	}

	Renderer2D::statistics Renderer2D::get_stats()
	{
		return _storage.stats;
	}
	
	void Renderer2D::reset_statistics()
	{
		memset(&_storage.stats, 0, sizeof(Renderer2D::statistics));
	}
}