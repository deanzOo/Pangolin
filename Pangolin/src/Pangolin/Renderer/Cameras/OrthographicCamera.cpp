#include "plpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pangolin {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: _projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _view_matrix(1.0f)
	{
		PL_PROFILE_FUNCTION();
		
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}

	void OrthographicCamera::set_projection(float left, float right, float bottom, float top) {
		PL_PROFILE_FUNCTION();
		
		_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}

	void OrthographicCamera::set_position(const glm::vec3& position)
	{
		_position = position;
		recalculate_view_matrix();
	}
	
	void OrthographicCamera::set_rotation(float rotation)
	{
		_rotation = rotation;
		recalculate_view_matrix();
	}
	
	void OrthographicCamera::recalculate_view_matrix()
	{
		PL_PROFILE_FUNCTION();
		
		glm::mat4 base_mtx			= glm::mat4(1.0f);
		glm::vec3 rotation_axis		= glm::vec3(0, 0, 1);
		glm::mat4 translated_mtx	= glm::translate(base_mtx, _position);
		glm::mat4 rotated_mtx		= glm::rotate(base_mtx, glm::radians(_rotation), rotation_axis);
		
		glm::mat4 transform			= translated_mtx * rotated_mtx;

		_view_matrix = glm::inverse(transform);
		_view_projection_matrix = _projection_matrix * _view_matrix;
	}
}