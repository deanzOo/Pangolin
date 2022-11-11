#include "gepch.h"
#include "App.h"
#include "Input.h"
#include "GamEngine/Renderer/Renderer.h"
#include <GamEngine/Renderer/Buffers/BufferLayout.h>

namespace GamEngine {

	App* App::instance = nullptr;

	App::App()
	{
		GE_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		_window = Scope<Window>(Window::create());
		_window->set_event_callback(GE_BIND_EVENT_FN(App::on_event));

		_time = Scope<Time>(Time::create());

		_imgui_layer = new ImGuiLayer();
		push_overlay(_imgui_layer);
	}

	App::~App()
	{
	}

	void App::on_event(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(App::on_window_close));

		for (auto it = _layer_stack.end(); it != _layer_stack.begin(); ) {
			(*--it)->on_event(e);
			if (e.is_handled())
				break;
		}
	}

	void App::push_layer(Layer* layer)
	{
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void App::push_overlay(Layer* layer)
	{
		_layer_stack.push_overlay(layer);
		layer->on_attach(); 
	}

	bool App::on_window_close(WindowCloseEvent& e) {
		_running = false;
		return true;
	}

	void App::run() {
		while (_running) {
			float time = _time->get_time();
			Timestep timestep = time - _last_frame_time;
			_last_frame_time = time;

			for (Layer* layer : _layer_stack)
				layer->on_update(timestep);

			_imgui_layer->begin();
			for (Layer* layer : _layer_stack)
				layer->on_imgui_render();
			_imgui_layer->end();

			_window->on_update();
		}
	}
}