#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "GamEngine/Events/Event.h"
#include "GamEngine/Events/AppEvent.h"
#include "GamEngine/Core/Time.h"
#include "GamEngine/Core/Timestep.h"

#include "GamEngine/ImGui/ImGuiLayer.h"

namespace GamEngine {
	class App
	{
	public:
		App();
		~App();
		void run();

		void on_event(Event& e);

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);

		inline static App& get() { return *instance; }
		inline Window& get_window() { return *_window; }

	private:
		bool on_window_close(WindowCloseEvent& e);
		bool on_window_resize(WindowResizeEvent& e);
	private:
		bool _running = true;
		bool _minimized = false;

		Scope<Window> _window;

		ImGuiLayer* _imgui_layer;
		LayerStack _layer_stack;

		Scope<Time> _time;
		float _last_frame_time;

		static App* instance;
	};
	App* create_app();
}


