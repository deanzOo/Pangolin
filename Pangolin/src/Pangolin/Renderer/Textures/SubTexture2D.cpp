#include "plpch.h"
#include "Pangolin\Renderer\Textures\SubTexture2D.h"

namespace Pangolin {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min_boundary, const glm::vec2& max_boundary)
		: _texture(texture)
	{
		_texture_coordinates[0] = min_boundary;
		_texture_coordinates[1] = { max_boundary.x, min_boundary.y };
		_texture_coordinates[2] = max_boundary;
		_texture_coordinates[3] = { min_boundary.x, max_boundary.y };
	}
	Ref<SubTexture2D> SubTexture2D::create_from_coordinates(const Ref<Texture2D>& texture, const glm::vec2& texture_coordinates, const glm::vec2& cell_size, const glm::vec2& sprite_size)
	{
		glm::vec2 min_boundary = {
			(texture_coordinates.x * cell_size.x) / texture->get_width(),
			(texture_coordinates.y * cell_size.y) / texture->get_height()
		};
		glm::vec2 max_boundary = {
			((texture_coordinates.x + sprite_size.x) * cell_size.x) / texture->get_width(),
			((texture_coordinates.y + sprite_size.y) * cell_size.y) / texture->get_height()
		};
		return create_ref<SubTexture2D>(texture, min_boundary, max_boundary);
	}
}
