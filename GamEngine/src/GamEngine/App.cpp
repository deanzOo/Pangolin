#include "gepch.h"
#include "App.h"
#include "Input.h"

namespace GamEngine {

	App* App::instance = nullptr;

	App::App()
	{
		GE_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(GE_BIND_EVENT_FN(App::on_event));
	}

	App::~App()
	{
	}

	void App::on_event(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(App::on_window_close));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); ) {
			(*--it)->on_event(e);
			if (e.is_handled())
				break;
		}
	}

	void App::push_layer(Layer* layer)
	{
		m_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void App::push_overlay(Layer* layer)
	{
		m_layer_stack.push_overlay(layer);
		layer->on_attach(); 
	}

	bool App::on_window_close(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	void App::run() {
		while (running) {
			for (Layer* layer : m_layer_stack)
				layer->on_update();

			m_window->on_update();
		}
	}
}