#pragma once

#include "Pangolin/Core/Core.h"

namespace Pangolin {

	class Input {
	public:
		static bool is_key_pressed(int keycode);
		
		static bool is_mouse_button_pressed(int button);
		static std::pair<float,float> get_mouse_position();
		static float get_mouse_x();
		static float get_mouse_y();
	};

}