#include <gamEngine.h>

class Sandbox : public gamEngine::App {
public:
	Sandbox() {}
};

gamEngine::App* gamEngine::CreateApp() {
	return new Sandbox();
}