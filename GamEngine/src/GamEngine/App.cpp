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

		GE_CORE_TRACE("{0}", e);
	}

	bool App::on_window_close(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	void App::run() {
		while (running)
			m_Window->on_update();
	}
}