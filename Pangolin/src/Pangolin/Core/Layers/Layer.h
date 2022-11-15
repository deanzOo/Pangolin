#pragma once

#include "Pangolin/Core/Core.h"
#include "Pangolin/Core/Time/Timestep.h"
#include "Pangolin/Events/Event.h"
#include "Pangolin/Events/MouseEvent.h"
#include "Pangolin/Events/KeyEvent.h"
#include "Pangolin/Events/AppEvent.h"

namespace Pangolin {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update(Timestep step) {}
		virtual void on_imgui_render() {}
		virtual void on_event(Event& event) {}

		inline const std::string& get_name() const { return m_debug_name; }
	protected:
		std::string m_debug_name;
	};
}

