#pragma once

#include "Pangolin/Core/Window.h"
#include "Pangolin/Renderer/Context.h"

struct GLFWwindow;

namespace Pangolin {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();
		
		void on_update() override;
		void set_vsync(bool enabled) override;

		inline unsigned int get_width() const override { return _data.width; }
		inline unsigned int get_height() const override { return _data.height; }
		inline bool is_vsync() const override { return _data.vsync; };

		inline void set_event_callback(const EventCallbackFn& callback) override { _data.event_callback = callback; }
	
		inline virtual void* get_native_window() const override { return _window; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

		GLFWwindow* _window;
		Context* _context;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vsync;

			EventCallbackFn event_callback;
		};

		WindowData _data;
	};

}