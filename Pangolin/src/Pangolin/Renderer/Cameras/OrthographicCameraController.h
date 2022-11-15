#pragma once

#include "OrthographicCamera.h"
#include "Pangolin/Core/Time/Timestep.h"

#include "Pangolin/Events/AppEvent.h"
#include "Pangolin/Events/MouseEvent.h"

namespace Pangolin {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void on_update(Timestep step);
		void on_event(Event& event);
		
		inline OrthographicCamera& get_camera() { return _camera; };
		inline const OrthographicCamera& get_camera() const { return _camera; };

		inline const void set_zoom_level(float zoom) { _zoom = zoom; };
		inline float get_zoom_level() { return _zoom; };
	private:
		bool on_mouse_scrolled(MouseScrolledEvent& event);
		bool on_window_resized(WindowResizeEvent& event);
	private:
		float _aspect_ratio;
		float _zoom = 1.0f;
		OrthographicCamera _camera;

		bool _rotation;
		glm::vec3 _camera_position = { 0.0f, 0.0f, 0.0f };
		float _camera_rotation = 0.0f;

		float _camera_translation_spd = 5.0f;
		float _camera_rotation_spd = 180.0f;
	};
}