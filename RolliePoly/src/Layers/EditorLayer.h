#pragma once

#include "Pangolin.h"

namespace Pangolin {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void on_attach() override;
		virtual void on_detach() override;
		virtual void on_update(Timestep step) override;
		virtual void on_imgui_render() override;
		virtual void on_event(Event& event) override;
	private:
		OrthographicCameraController _camera_controller;

		Ref<Texture2D> _texture;
		Ref<Texture2D> _sprite_sheet;
		Ref<SubTexture2D> _stairs_sprite;
		Ref<SubTexture2D> _barrel_sprite;
		Ref<SubTexture2D> _tree_sprite;
		Ref<FrameBuffer> _frame_buffer;

		glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };

		glm::vec2 _viewport_size = glm::vec2(0);
		bool _viewport_focused = false;
		bool _viewport_hovered = false;

		float _rotation = 0.0f;
	};
}