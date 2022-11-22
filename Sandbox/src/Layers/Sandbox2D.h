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

	glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };
};