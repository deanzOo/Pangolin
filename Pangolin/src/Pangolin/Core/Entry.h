#pragma once

#ifdef PL_PLATFORM_WINDOWS

extern Pangolin::App* Pangolin::create_app();

int main(int argc, char** argv) {
	Pangolin::Log::init();

	PL_PROFILE_BEGIN_SESSION("Startup", "PangolinProfile-Startup.json");
	auto app = Pangolin::create_app();
	PL_PROFILE_END_SESSION();

	PL_PROFILE_BEGIN_SESSION("Runtime", "PangolinProfile-Runtime.json");
	app->run();
	PL_PROFILE_END_SESSION();

	PL_PROFILE_BEGIN_SESSION("Shutdown", "PangolinProfile-Shutdown.json");
	delete app;
	PL_PROFILE_END_SESSION();

	return 0;
}
#endif