#pragma once

namespace GamEngine {
	class Timestep {
	public:
		Timestep(float time = 0.0f) : _time(time)
		{
		};

		operator float() const { return _time; }

		float get_seconds() const { return _time; }
		float get_milliseconds() const { return _time * 1000.0f; }
	private:
		float _time;
	};
}