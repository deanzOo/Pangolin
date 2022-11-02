#pragma once

#include "gepch.h"

#include "GamEngine/Core.h"
#include "GamEngine/Events/Event.h"

namespace GamEngine {
	struct WindowProps {
		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;

		WindowProps(const std::string& title = "GamEngine", unsigned int width = 1280, unsigned int height = 720) : m_title(title), m_width(width), m_height(height) {}
	};

	class GE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void on_update() = 0;

		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		virtual void set_event_callback(const EventCallbackFn& callback) = 0;
		virtual void set_vsync(bool enabled) = 0;
		virtual bool is_vsync() const = 0;

		static Window* create(const WindowProps& props = WindowProps());
		
		virtual void* get_native_window() const = 0;
	};
}