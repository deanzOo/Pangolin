#include "gepch.h"
#include "App.h"
#include "GamEngine/Renderer/Renderer.h"

namespace GamEngine {

	App* App::instance = nullptr;

	App::App()
	{
		GE_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		_window = Scope<Window>(Window::create());
		_window->set_event_callback(GE_BIND_EVENT_FN(App::on_event));

		_time = Scope<Time>(Time::create());

		Renderer::init();

		_imgui_layer = new ImGuiLayer();
		push_overlay(_imgui_layer);
	}

	App::~App()
	{
	}

	void App::on_event(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(App::on_window_close));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(App::on_window_resize));

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

	bool App::on_window_close(WindowCloseEvent& event) {
		_running = false;
		return true;
	}

	bool App::on_window_resize(WindowResizeEvent& event)
	{
		uint32_t window_width = event.get_window_width(), window_height = event.get_window_height();
		if (window_width == 0 || window_height == 0) {
			_minimized = true;
			return false;
		}
		_minimized = false;

		Renderer::on_window_resize(window_width, window_height);

		return false;
	}

	void App::run() {
		while (_running) {
			float time = _time->get_time();
			Timestep timestep = time - _last_frame_time;
			_last_frame_time = time;

			if (!_minimized) {
				for (Layer* layer : _layer_stack)
					layer->on_update(timestep);

				_imgui_layer->begin();
				for (Layer* layer : _layer_stack)
					layer->on_imgui_render();
				_imgui_layer->end();
			}

			_window->on_update();
		}
	}
}