#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GamEngine::App* GamEngine::create_app();

int main(int argc, char** argv) {
	GamEngine::Log::init();
	GE_CORE_WARN("Initialized Log!");
	GE_CLIENT_WARN("Initialized Log!");

	auto app = GamEngine::create_app();
	app->run();
	delete app;

	return 0;
}
#endif