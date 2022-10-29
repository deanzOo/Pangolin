#pragma once

#include "Event.h"

#include <sstream>

namespace GamEngine {

	class GE_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : window_width(width), window_height(height) {}

		inline unsigned int get_window_width() const { return window_width; }
		inline unsigned int get_window_height() const { return window_height; }

		std::string ToString() const override{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << window_width << ", " << window_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApp)
	private:
		unsigned int window_width, window_height;
	};

	class GE_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class GE_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class GE_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

	class GE_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApp)
	};

}
