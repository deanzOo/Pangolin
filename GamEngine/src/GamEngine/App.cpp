#include "gepch.h"
#include "App.h"

namespace GamEngine {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->set_event_callback(BIND_EVENT_FN(App::on_event));
	}

	App::~App()
	{
	}

	void App::on_event(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::on_window_close));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); ) {
			(*--it)->on_event(e);
			if (e.is_handled())
				break;
		}
	}

	void App::push_layer(Layer* layer)
	{
		m_layer_stack.push_layer(layer);
	}

	void App::push_overlay(Layer* layer)
	{
		m_layer_stack.pop_overlay(layer);
	}

	bool App::on_window_close(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	void App::run() {
		while (running) {
			for (Layer* layer : m_layer_stack)
				layer->on_update();
			m_Window->on_update();
		}
	}
}