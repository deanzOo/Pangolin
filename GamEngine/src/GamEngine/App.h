#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace GamEngine {
	class GE_API App
	{
	public:
		App();
		~App();
		void run();
	private:
		std::unique_ptr<Window> m_Window;
		bool running = true;
	};

	App* create_app();
}


