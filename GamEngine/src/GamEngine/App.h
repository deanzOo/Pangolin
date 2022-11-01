#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "GamEngine/Events/AppEvent.h"
#include "Window.h"
#include "LayerStack.h"

namespace GamEngine {
	class GE_API App
	{
	public:
		App();
		~App();
		void run();

		void on_event(Event& e);

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);

		inline static App& get() { return *instance; }
		inline Window& get_window() { return *m_window; }
	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		bool running = true;
		LayerStack m_layer_stack;

		static App* instance;
	};
	App* create_app();
}


