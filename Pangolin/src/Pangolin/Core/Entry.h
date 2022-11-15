#pragma once

#ifdef PL_PLATFORM_WINDOWS

extern Pangolin::App* Pangolin::create_app();

int main(int argc, char** argv) {
	Pangolin::Log::init();
	PL_CORE_WARN("Initialized Log!");
	PL_CLIENT_WARN("Initialized Log!");

	auto app = Pangolin::create_app();
	app->run();
	delete app;

	return 0;
}
#endif