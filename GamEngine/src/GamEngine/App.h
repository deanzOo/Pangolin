#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "GamEngine/Events/AppEvent.h"
#include "Window.h"

namespace GamEngine {
	class GE_API App
	{
	public:
		App();
		~App();
		void run();

		void on_event(Event& e);
	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool running = true;
	};
	App* create_app();
}


