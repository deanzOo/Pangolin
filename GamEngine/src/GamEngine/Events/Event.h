#pragma once

#include "gepch.h"
#include "GamEngine/Core/Core.h"

namespace GamEngine {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None						= 0,
		EventCategoryApp			= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::type; } \
								virtual EventType get_event_type() const override { return get_static_type(); } \
								virtual const char* get_event_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	class Event {
		friend class EventDispatcher;
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_event_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string ToString() const { return get_event_name(); }

		inline bool is_in_category(EventCategory category) {
			return get_category_flags() & (int)category;
		}

		inline bool is_handled() { return handled; }
	protected:
		bool handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)> ;
	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template<typename T>
		bool dispatch(EventFn<T> func) {
			if (m_event.get_event_type() == T::get_static_type()) {
				m_event.handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}