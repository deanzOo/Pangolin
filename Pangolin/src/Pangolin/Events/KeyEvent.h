#pragma once

#include "Event.h"

namespace Pangolin {
	class KeyEvent : public Event {
	public:
		inline unsigned int get_codepoint() const { return m_codepoint; }
		inline int get_keycode() const { return m_keycode; }
		inline int get_scancode() const { return m_scancode; }
		inline int get_mods() const { return m_mods; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode, int scancode, int mods) : m_keycode(keycode), m_scancode(scancode), m_mods(mods) {}
		KeyEvent(unsigned int codepoint) : m_codepoint(codepoint) {}

		int m_keycode, m_scancode, m_mods;
		unsigned int m_codepoint;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int scancode, int mods, int repeat_count) : KeyEvent(keycode, scancode, mods), m_repeat_count(repeat_count) {}

		inline int get_repeat_count() const { return m_repeat_count; }

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_repeat_count;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode, int scancode, int mods) : KeyEvent(keycode, scancode, mods) {}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

			EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(unsigned int codepoint) : KeyEvent(codepoint) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_codepoint;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}