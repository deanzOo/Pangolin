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

	Pangolin::Ref<Pangolin::VertexArray> _square_vertex_array;
	Pangolin::Ref<Pangolin::VertexBuffer> _square_vertex_buffer;
	Pangolin::Ref<Pangolin::IndexBuffer> _square_index_buffer;
	Pangolin::Ref<Pangolin::Shader> _flat_color_shader;
	glm::vec3 _square_pos = { 0.0f, 0.0f, 0.0f };
	glm::vec4 _square_color = { 0.2f, 0.3f, 0.8f, 1.0f };
};