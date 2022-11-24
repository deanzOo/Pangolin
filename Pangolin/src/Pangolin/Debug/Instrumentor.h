#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Pangolin {
	struct profile_result
	{
		std::string name;
		long long start, end;
		uint32_t thread_id;
	};

	struct InstrumentationSession
	{
		std::string name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* _current_session;
		std::ofstream _output_stream;
		int _profile_count;
	public:
		Instrumentor()
			: _current_session(nullptr), _profile_count(0)
		{
		}

		void begin_session(const std::string& name, const std::string& filepath = "results.json")
		{
			_output_stream.open(filepath);
			write_header();
			_current_session = new InstrumentationSession{ name };
		}

		void end_session()
		{
			write_footer();
			_output_stream.close();
			delete _current_session;
			_current_session = nullptr;
			_profile_count = 0;
		}

		void write_profile(const profile_result& result)
		{
			if (_profile_count++ > 0)
				_output_stream << ",";

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			_output_stream << "{";
			_output_stream << "\"cat\":\"function\",";
			_output_stream << "\"dur\":" << (result.end - result.start) << ',';
			_output_stream << "\"name\":\"" << name << "\",";
			_output_stream << "\"ph\":\"X\",";
			_output_stream << "\"pid\":0,";
			_output_stream << "\"tid\":" << result.thread_id << ",";
			_output_stream << "\"ts\":" << result.start;
			_output_stream << "}";

			_output_stream.flush();
		}

		void write_header()
		{
			_output_stream << "{\"otherData\": {},\"traceEvents\":[";
			_output_stream.flush();
		}

		void write_footer()
		{
			_output_stream << "]}";
			_output_stream.flush();
		}

		static Instrumentor& get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: _name(name), _stopped(false)
		{
			_start_timepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!_stopped)
				stop();
		}

		void stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_start_timepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::get().write_profile({ _name, start, end, thread_id });

			_stopped = true;
		}
	private:
		const char* _name;
		std::chrono::time_point<std::chrono::high_resolution_clock> _start_timepoint;
		bool _stopped;
	};
}

#define PL_PROFILE 0
#if PL_PROFILE
#define PL_PROFILE_BEGIN_SESSION(name, filepath) ::Pangolin::Instrumentor::get().begin_session(name, filepath)
#define PL_PROFILE_END_SESSION() ::Pangolin::Instrumentor::get().end_session()
#define PL_PROFILE_SCOPE(name) ::Pangolin::InstrumentationTimer timer##__LINE__(name);
#define PL_PROFILE_FUNCTION() PL_PROFILE_SCOPE(__FUNCSIG__)
#else
#define PL_PROFILE_BEGIN_SESSION(name, filepath)
#define PL_PROFILE_END_SESSION()
#define PL_PROFILE_SCOPE(name)
#define PL_PROFILE_FUNCTION()
#endif