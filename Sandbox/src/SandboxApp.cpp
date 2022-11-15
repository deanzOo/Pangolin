#include "Pangolin.h"
#include "ExampleLayer.h"

class Sandbox : public Pangolin::App {
public:
	Sandbox() {
		push_layer(new ExampleLayer());
	}
};

Pangolin::App* Pangolin::create_app() {
	return new Sandbox();
}