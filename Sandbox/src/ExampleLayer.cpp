#include "ExampleLayer.h"

ExampleLayer::ExampleLayer() : Layer("Exmaple") {
}

void ExampleLayer::on_event(GamEngine::Event& event) {
	if (event.get_event_type() == GamEngine::EventType::KeyPressed) {
		GamEngine::KeyPressedEvent& e = (GamEngine::KeyPressedEvent&)event;
		GE_CLIENT_TRACE("{0}", (char)e.get_keycode());
	}
}