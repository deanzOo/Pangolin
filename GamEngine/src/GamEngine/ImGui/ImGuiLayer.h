#pragma once

#include "GamEngine/Layer.h";

namespace GamEngine{
	class GE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach();
		void on_detach();
		void on_update();
		void on_event(Event& event);
	private:
		bool on_mouse_button_pressed_event(MouseButtonPressedEvent& event);
		bool on_mouse_button_released_event(MouseButtonReleasedEvent& event);
		bool on_mouse_moved_event(MouseMovedEvent& event);
		bool on_mouse_scrolled_event(MouseScrolledEvent& event);

		bool on_key_pressed_event(KeyPressedEvent& event);
		bool on_key_released_event(KeyReleasedEvent& event);
		bool on_key_typed_event(KeyTypedEvent& event);

		bool on_window_resize_event(WindowResizeEvent& evnet);
	private:
		float m_time = 0.0f;
	};
}