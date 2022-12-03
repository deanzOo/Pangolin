#pragma once

#include "Pangolin/Core/Layers/Layer.h"

namespace Pangolin {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void on_attach() override;
		void on_detach() override;
		void on_event(Event& event) override;

		void begin();
		void end();

		void set_block_events(bool block) { _blocking_events = block; }
	private:
		bool _blocking_events = true;
		float m_time = 0.0f;
	};
}