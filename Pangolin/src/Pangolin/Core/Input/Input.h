#pragma once

#include "Pangolin/Core/Core.h"

namespace Pangolin {

	class Input {
	public:
		inline static bool is_key_pressed(int keycode) { return instance->is_key_pressed_impl(keycode); };
		inline static bool is_mouse_button_pressed(int button) { return instance->is_mouse_button_pressed_impl(button); };
		inline static std::pair<float,float> get_mouse_position() { return instance->get_mouse_position_impl(); };
		inline static float get_mouse_x() { return instance->get_mouse_x_impl(); };
		inline static float get_mouse_y() { return instance->get_mouse_y_impl(); };
	protected:
		virtual bool is_key_pressed_impl(int keycode) = 0;
		virtual bool is_mouse_button_pressed_impl(int button) = 0;
		virtual std::pair<float,float> get_mouse_position_impl() = 0;
		virtual float get_mouse_x_impl() = 0;
		virtual float get_mouse_y_impl() = 0;
	private:
		static Input* instance;
	};

}