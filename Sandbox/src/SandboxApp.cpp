#include <GamEngine.h>

class ExampleLayer : public GamEngine::Layer {
public:
	ExampleLayer() : Layer("Exmaple") {}

	void on_update() override {
		if (GamEngine::Input::is_key_pressed(GE_KEY_TAB))
			GE_CLIENT_TRACE("Tab key is pressed (poll)!");
	}

	void on_event(GamEngine::Event& event) override {
		if (event.get_event_type() == GamEngine::EventType::KeyPressed) {
			GamEngine::KeyPressedEvent& e= (GamEngine::KeyPressedEvent&)event;
			if (e.get_keycode() == GE_KEY_TAB)
				GE_CLIENT_TRACE("Tab is pressed (event)!");
			GE_CLIENT_TRACE("{0}", (char)e.get_keycode());
		}
	}
};

class Sandbox : public GamEngine::App {
public:
	Sandbox() {
		push_layer(new ExampleLayer);
	}
};

GamEngine::App* GamEngine::create_app() {
	return new Sandbox();
}