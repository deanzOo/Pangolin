#pragma once

namespace Pangolin {
	class Time {
	public:
		virtual ~Time() {}

		virtual float get_time() const = 0;

		static Time* create();
	};
}