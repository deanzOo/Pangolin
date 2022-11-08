#pragma once

#include "Core.h"
#include "GamEngine/Events/Event.h"
#include "GamEngine/Events/AppEvent.h"
#include "Window.h"
#include "LayerStack.h"

#include "GamEngine/ImGui/ImGuiLayer.h"

#include "GamEngine/Renderer/Shaders/Shader.h"
#include <GamEngine/Renderer/Buffers/VertexBuffer.h>
#include <GamEngine/Renderer/Buffers/IndexBuffer.h>
#include <GamEngine/Renderer/Arrays/VertexArray.h>

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
		inline Window& get_window() { return *m_window; }

	private:
		bool on_window_close(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imgui_layer;
		bool running = true;
		LayerStack m_layer_stack;

		static App* instance;
	};
	App* create_app();
}


