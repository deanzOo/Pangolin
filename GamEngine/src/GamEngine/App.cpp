#include "gepch.h"
#include "App.h"

namespace GamEngine {
	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::create());
	}
	App::~App()
	{
	}
	void App::run() {
		while (running)
			m_Window->on_update();
	}
}