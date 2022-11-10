#include "GamEngine.h"
#include "ExampleLayer.h"

class Sandbox : public GamEngine::App {
public:
	Sandbox() {
		push_layer(new ExampleLayer());
	}
};

GamEngine::App* GamEngine::create_app() {
	return new Sandbox();
}