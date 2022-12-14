#include "plpch.h"
#include "App.h"
#include "Pangolin/Renderer/Renderer.h"

namespace Pangolin {

	App* App::instance = nullptr;

	App::App(const std::string& title)
	{
		PL_PROFILE_FUNCTION();
		
		PL_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		_window = Scope<Window>(Window::create(WindowProps(title)));
		_window->set_event_callback(PL_BIND_EVENT_FN(App::on_event));

		_time = Scope<Time>(Time::create());

		Renderer::init();

		_imgui_layer = new ImGuiLayer();
		push_overlay(_imgui_layer);
	}

	App::~App()
	{
		PL_PROFILE_FUNCTION();
		
		Renderer::shutdown();
	}

	void App::on_event(Event& e) {
		PL_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(PL_BIND_EVENT_FN(App::on_window_close));
		dispatcher.dispatch<WindowResizeEvent>(PL_BIND_EVENT_FN(App::on_window_resize));

		for (auto it = _layer_stack.end(); it != _layer_stack.begin(); ) {
			if (e.is_handled())
				break;
			(*--it)->on_event(e);
		}
	}

	void App::push_layer(Layer* layer)
	{
		PL_PROFILE_FUNCTION();
		
		_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void App::push_overlay(Layer* layer)
	{
		PL_PROFILE_FUNCTION();
		
		_layer_stack.push_overlay(layer);
		layer->on_attach(); 
	}

	void App::close()
	{
		_running = false;
	}

	bool App::on_window_close(WindowCloseEvent& event) {
		_running = false;
		return true;
	}

	bool App::on_window_resize(WindowResizeEvent& event)
	{
		PL_PROFILE_FUNCTION();
		
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
		PL_PROFILE_FUNCTION();
		
		while (_running) {
			PL_PROFILE_SCOPE("App::run-loop");
			float time = _time->get_time();
			Timestep timestep = time - _last_frame_time;
			_last_frame_time = time;

			if (!_minimized) {
				{
					PL_PROFILE_SCOPE("App::run-layers::on_update")
					
					for (Layer* layer : _layer_stack)
						layer->on_update(timestep);
				}

				_imgui_layer->begin();
				{
					PL_PROFILE_SCOPE("App::run-imgui_layers::on_update")

					for (Layer* layer : _layer_stack)
						layer->on_imgui_render();
				}
				_imgui_layer->end();
			}

			_window->on_update();
		}
	}
}