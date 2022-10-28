#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern gamEngine::App* gamEngine::CreateApp();

int main(int argc, char** argv) {
	auto app = gamEngine::CreateApp();
	app->Run();
	delete app;

	return 0;
}
#endif