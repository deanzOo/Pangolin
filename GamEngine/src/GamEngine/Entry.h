#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GamEngine::App* GamEngine::CreateApp();

int main(int argc, char** argv) {
	GamEngine::Log::Init();
	GE_CORE_WARN("Initialized Log!");
	GE_CLIENT_WARN("Initialized Log!");

	auto app = GamEngine::CreateApp();
	app->Run();
	delete app;

	return 0;
}
#endif