#include "Log.h"

namespace GamEngine {
	std::shared_ptr<spdlog::logger> Log::core_logger;
	std::shared_ptr<spdlog::logger> Log::client_logger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		core_logger = spdlog::stdout_color_mt("GamEngine");
		core_logger->set_level(spdlog::level::trace);

		client_logger = spdlog::stdout_color_mt("App");
		client_logger->set_level(spdlog::level::trace);
	}
}