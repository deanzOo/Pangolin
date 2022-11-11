#pragma once

#include "GamEngine/Core/Time.h"

struct GLFWwindow;

namespace GamEngine {

	class WindowsTime : public Time {
	public:
		WindowsTime() {};
		~WindowsTime() {};

		virtual float get_time() const override;
	};

}