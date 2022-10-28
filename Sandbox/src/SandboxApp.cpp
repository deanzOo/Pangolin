#include <GamEngine.h>

class Sandbox : public GamEngine::App {
public:
	Sandbox() {}
};

GamEngine::App* GamEngine::CreateApp() {
	return new Sandbox();
}