#pragma once

#include <glm/glm.hpp>

namespace Pangolin {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		
		void set_projection(float left, float right, float bottom, float top);

		const glm::vec3 get_position() const { return _position; }
		float get_rotation() const { return _rotation; }

		void set_position(const glm::vec3& position);
		void set_rotation(float rotation);

		const glm::mat4& get_projection_matrix() const { return _projection_matrix; }
		const glm::mat4& get_view_matrix() const { return _view_matrix; }
		const glm::mat4& get_view_projection_matrix() const { return _view_projection_matrix; }
	private:
		void recalculate_view_matrix();
	private:
		glm::mat4 _projection_matrix;
		glm::mat4 _view_matrix;
		glm::mat4 _view_projection_matrix;

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		float _rotation = 0.0f;
	};
}