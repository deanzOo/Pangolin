#pragma once

#include "Pangolin/Core/Time/Time.h"

struct GLFWwindow;

namespace Pangolin {

	class WindowsTime : public Time {
	public:
		WindowsTime() {};
		~WindowsTime() {};

		virtual float get_time() const override;
	};

}