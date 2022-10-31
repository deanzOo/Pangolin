#pragma once

#include "GamEngine/Core.h"
#include "GamEngine/Events/Event.h"

namespace GamEngine {
	class GE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_event(Event& event) {}

		inline const std::string& get_name() const { return m_debug_name; }
	protected:
		std::string m_debug_name;
	};
}

