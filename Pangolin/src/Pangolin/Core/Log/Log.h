#pragma once

#include "Pangolin/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Pangolin {
	class Log {
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger;
		static std::shared_ptr<spdlog::logger> client_logger;
	};
}

#define GE_CORE_TRACE(...)		::Pangolin::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define GE_CORE_WARN(...)		::Pangolin::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define GE_CORE_CRITICAL(...)	::Pangolin::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define GE_CORE_DEBUG(...)		::Pangolin::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define GE_CORE_ERROR(...)		::Pangolin::Log::GetCoreLogger()->error(__VA_ARGS__);
#define GE_CORE_INFO(...)		::Pangolin::Log::GetCoreLogger()->info(__VA_ARGS__);

#define GE_CLIENT_TRACE(...)	::Pangolin::Log::GetClientLogger()->trace(__VA_ARGS__);
#define GE_CLIENT_WARN(...)		::Pangolin::Log::GetClientLogger()->warn(__VA_ARGS__);
#define GE_CLIENT_CRITICAL(...) ::Pangolin::Log::GetClientLogger()->critical(__VA_ARGS__);
#define GE_CLIENT_DEBUG(...)	::Pangolin::Log::GetClientLogger()->debug(__VA_ARGS__);
#define GE_CLIENT_ERROR(...)	::Pangolin::Log::GetClientLogger()->error(__VA_ARGS__);
#define GE_CLIENT_INFO(...)		::Pangolin::Log::GetClientLogger()->info(__VA_ARGS__);