#pragma once

#include "Cameras/OrthographicCamera.h"
#include "Textures/Texture2D.h"

namespace Pangolin {

	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void begin_scene(OrthographicCamera& camera);
		static void end_scene();

		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);
	};

}