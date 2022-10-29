#pragma once

#include "Event.h"

#include <sstream>

namespace GamEngine {

	class GE_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : mouse_x(x), mouse_y(y) {}

		inline float GetX() const { return mouse_x; }
		inline float GetY() const { return mouse_y; }

		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouse_x << ", " << mouse_y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouse_x, mouse_y;
	};

	class GE_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x_offset, float y_offset) : mouse_x_offset(x_offset), mouse_y_offset(y_offset) {}

		inline float get_x_offset() const { return mouse_x_offset; }
		inline float get_y_offset() const { return mouse_y_offset; }

		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << mouse_x_offset << ", " << mouse_y_offset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mouse_x_offset, mouse_y_offset;
	};

	class GE_API MouseButtonEvent : public Event {
	public:
		inline int get_mouse_button() const { return mouse_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : mouse_button(button) {}
		float mouse_button;
	};

	class GE_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button): MouseButtonEvent(button) {}
		
		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mouse_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class GE_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mouse_button;
			return ss.str();
		}

			EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}