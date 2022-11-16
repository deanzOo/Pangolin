#pragma once

#include "Pangolin.h"

class TilemapLayer : public Pangolin::Layer {
public:
	TilemapLayer();

	virtual void on_update(Pangolin::Timestep step) override;
	virtual void on_imgui_render() override;
	void on_event(Pangolin::Event& event) override;

private:
	Pangolin::Ref<Pangolin::Shader> _flat_color_shader;

	Pangolin::Ref<Pangolin::VertexArray> _square_vertex_array;
	Pangolin::Ref<Pangolin::VertexBuffer> _square_vertex_buffer;
	Pangolin::Ref<Pangolin::IndexBuffer> _square_index_buffer;
	glm::vec3 _square_color = { 0.2f, 0.3f, 0.8f };

	Pangolin::OrthographicCameraController _camera_controller;
};