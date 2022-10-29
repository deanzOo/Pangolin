#include <GamEngine.h>

class Sandbox : public GamEngine::App {
public:
	Sandbox() {}
};

GamEngine::App* GamEngine::create_app() {
	return new Sandbox();
}