#pragma once

#include <glm/glm.hpp>
#include "Pangolin/Renderer/Textures/Texture2D.h"

namespace Pangolin
{
	class SubTexture2D
	{
	public: 
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min_bound, const glm::vec2& max_bound);

		inline const Ref<Texture2D>  get_texture() const { return _texture; }
		inline const glm::vec2* get_texture_coordinates() const { return _texture_coordinates; }

		static Ref<SubTexture2D> create_from_coordinates(const Ref<Texture2D>& texture, const glm::vec2& texture_coordinates, const glm::vec2& cell_size, const glm::vec2& sprite_size = glm::vec2(1.0f));
	private:
		Ref<Texture2D> _texture;
		glm::vec2 _texture_coordinates[4];
	};

}