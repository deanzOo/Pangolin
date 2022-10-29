#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GamEngine {
	class GE_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger;
		static std::shared_ptr<spdlog::logger> client_logger;
	};
}

#define GE_CORE_TRACE(...)		::GamEngine::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define GE_CORE_WARN(...)		::GamEngine::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define GE_CORE_CRITICAL(...)	::GamEngine::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define GE_CORE_DEBUG(...)		::GamEngine::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define GE_CORE_ERROR(...)		::GamEngine::Log::GetCoreLogger()->error(__VA_ARGS__);
#define GE_CORE_INFO(...)		::GamEngine::Log::GetCoreLogger()->info(__VA_ARGS__);

#define GE_CLIENT_TRACE(...)	::GamEngine::Log::GetClientLogger()->trace(__VA_ARGS__);
#define GE_CLIENT_WARN(...)		::GamEngine::Log::GetClientLogger()->warn(__VA_ARGS__);
#define GE_CLIENT_CRITICAL(...) ::GamEngine::Log::GetClientLogger()->critical(__VA_ARGS__);
#define GE_CLIENT_DEBUG(...)	::GamEngine::Log::GetClientLogger()->debug(__VA_ARGS__);
#define GE_CLIENT_ERROR(...)	::GamEngine::Log::GetClientLogger()->error(__VA_ARGS__);
#define GE_CLIENT_INFO(...)		::GamEngine::Log::GetClientLogger()->info(__VA_ARGS__);