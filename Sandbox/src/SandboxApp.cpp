#include "Pangolin.h"

#include "Pangolin/Core/Entry.h"

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Pangolin::App {
public:
	Sandbox() {
		//push_layer(new ExampleLayer());
		push_layer(new Sandbox2D());
	}
};

Pangolin::App* Pangolin::create_app() {
	return new Sandbox();
}