#pragma once

#include "Cameras/OrthographicCamera.h"
#include "Textures/Texture2D.h"
#include <glm/detail/type_float.hpp>

namespace Pangolin {

	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void begin_scene(OrthographicCamera& camera);
		static void end_scene();

		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tile_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tile_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		
		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void draw_rotated_quad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tile_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
		static void draw_rotated_quad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tile_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
	};

}