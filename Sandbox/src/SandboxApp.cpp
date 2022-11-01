#include <GamEngine.h>

class Sandbox : public GamEngine::App {
public:
	Sandbox() {
		push_overlay(new GamEngine::ImGuiLayer());
	}
};

GamEngine::App* GamEngine::create_app() {
	return new Sandbox();
}