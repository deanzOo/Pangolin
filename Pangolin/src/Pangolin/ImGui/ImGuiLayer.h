#pragma once

#include "Pangolin/Core/Layers/Layer.h"

namespace Pangolin {
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