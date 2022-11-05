#pragma once

#include "GamEngine/Core/Layer.h"

namespace GamEngine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void on_attach() override;
		void on_detach() override;
		void on_imgui_render() override;

		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};
}