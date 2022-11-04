#pragma once

#include "Event.h"

namespace GamEngine {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : mouse_x(x), mouse_y(y) {}

		inline float get_x() const { return mouse_x; }
		inline float get_y() const { return mouse_y; }

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

	class MouseScrolledEvent : public Event {
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

	class MouseButtonEvent : public Event {
	public:
		inline int get_button() const { return m_button; }
		inline int get_mods() const { return m_mods; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button, int mods) : m_button(button), m_mods(mods) {}
		int m_button, m_mods;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button, int mods): MouseButtonEvent(button, mods) {}
		
		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button, int mods) : MouseButtonEvent(button, mods) {}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

			EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}