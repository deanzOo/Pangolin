#include "ExampleLayer.h"
#include "GamEngine.h"

class Sandbox : public GamEngine::App {
public:
	Sandbox() {
		push_layer(new ExampleLayer());
	}
};

GamEngine::App* GamEngine::create_app() {
	return new Sandbox();
}