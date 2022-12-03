#include "plpch.h"
#include "OrthographicCameraController.h"
#include "Pangolin/Core/Input/Input.h"
#include "Pangolin/Core/Input/KeyCodes.h"

namespace Pangolin {
	static KeyCode keycode;
	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
		: _camera(-_aspect_ratio * _zoom, _aspect_ratio * _zoom, -_zoom, _zoom), _aspect_ratio(aspect_ratio), _rotation(rotation)
	{
	}

	void OrthographicCameraController::on_update(Timestep step)
	{
		PL_PROFILE_FUNCTION();
		
		if (Input::is_key_pressed(Keys::W)) _camera_position.y += _camera_translation_spd * step;
		else if (Input::is_key_pressed(Keys::A)) _camera_position.x -= _camera_translation_spd * step;
		else if (Input::is_key_pressed(Keys::S)) _camera_position.y -= _camera_translation_spd * step;
		else if (Input::is_key_pressed(Keys::D)) _camera_position.x += _camera_translation_spd * step;
		if (_rotation) {
			if (Input::is_key_pressed(Keys::E)) _camera_rotation += _camera_rotation_spd * step;
			else if (Input::is_key_pressed(Keys::Q)) _camera_rotation -= _camera_rotation_spd * step;
			_camera.set_rotation(_camera_rotation);
		}

		_camera.set_position(_camera_position);
		_camera_translation_spd = _zoom;
	}

	void OrthographicCameraController::on_event(Event& event)
	{
		PL_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseScrolledEvent>(PL_BIND_EVENT_FN(OrthographicCameraController::on_mouse_scrolled));
		dispatcher.dispatch<WindowResizeEvent>(PL_BIND_EVENT_FN(OrthographicCameraController::on_window_resized));
	}

	void OrthographicCameraController::on_resize(float width, float height)
	{
		PL_PROFILE_FUNCTION();

		_aspect_ratio = width / height;
		_camera.set_projection(-_aspect_ratio * _zoom, _aspect_ratio * _zoom, -_zoom, _zoom);
	}

	bool OrthographicCameraController::on_mouse_scrolled(MouseScrolledEvent& event)
	{
		PL_PROFILE_FUNCTION();
		
		_zoom -= event.get_y_offset() * 0.25f;
		_zoom = std::max(_zoom, 0.25f);
		_camera.set_projection(-_aspect_ratio * _zoom, _aspect_ratio * _zoom, -_zoom, _zoom);

		return false;
	}

	bool OrthographicCameraController::on_window_resized(WindowResizeEvent& event)
	{
		PL_PROFILE_FUNCTION();
		
		on_resize((float)event.get_window_width(), (float)event.get_window_height());

		return false;
	}
}