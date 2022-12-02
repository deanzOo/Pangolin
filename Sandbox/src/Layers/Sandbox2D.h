#pragma once

#include "Pangolin.h"

class Sandbox2D : public Pangolin::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update(Pangolin::Timestep step) override;
	virtual void on_imgui_render() override;
	virtual void on_event(Pangolin::Event& event) override;
private:
	Pangolin::OrthographicCameraController _camera_controller;

	Pangolin::Ref<Pangolin::Texture2D> _texture;
	Pangolin::Ref<Pangolin::Texture2D> _sprite_sheet;
	Pangolin::Ref<Pangolin::SubTexture2D> _stairs_sprite;
	Pangolin::Ref<Pangolin::SubTexture2D> _barrel_sprite;
	Pangolin::Ref<Pangolin::SubTexture2D> _tree_sprite;
	Pangolin::Ref<Pangolin::FrameBuffer> _frame_buffer;

	glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };

	float _rotation = 0.0f;
};