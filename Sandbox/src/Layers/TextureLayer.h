#pragma once

#include "Pangolin.h"

class TextureLayer : public Pangolin::Layer {
public:
	TextureLayer();

	virtual void on_update(Pangolin::Timestep step) override;
	void on_event(Pangolin::Event& event) override;

private:
	Pangolin::Ref<Pangolin::Shader> _texture_shader;
	Pangolin::Ref<Pangolin::Texture2D> _texture;

	Pangolin::Ref<Pangolin::VertexArray> _square_vertex_array;
	Pangolin::Ref<Pangolin::VertexBuffer> _square_vertex_buffer;
	Pangolin::Ref<Pangolin::IndexBuffer> _square_index_buffer;
	glm::vec3 _square_pos = { 0.0f, 0.0f, 0.0f };

	Pangolin::OrthographicCameraController _camera_controller;
};