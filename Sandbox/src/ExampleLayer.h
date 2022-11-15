#pragma once

#include "Pangolin/Core/Layers/Layer.h"
#include "Pangolin/Core/Time/Timestep.h"
#include <Pangolin/Renderer/Shaders/Shader.h>
#include <Pangolin/Renderer/Shaders/ShaderLibrary.h>
#include <Pangolin/Renderer/Arrays/VertexArray.h>
#include "Pangolin/Renderer/Cameras/OrthographicCamera.h"
#include "Pangolin/Renderer/Cameras/OrthographicCameraController.h"
#include "Pangolin/Renderer/Textures/Texture2D.h"

class ExampleLayer : public Pangolin::Layer {
public:
	ExampleLayer();

	virtual void on_update(Pangolin::Timestep step) override;
	virtual void on_imgui_render() override;
	void on_event(Pangolin::Event& event) override;

private:
	Pangolin::ShaderLibrary _shader_library;

	Pangolin::Ref<Pangolin::Texture2D> _texture;

	Pangolin::Ref<Pangolin::VertexArray> _square_vertex_array;
	Pangolin::Ref<Pangolin::VertexBuffer> _square_vertex_buffer;
	Pangolin::Ref<Pangolin::IndexBuffer> _square_index_buffer;
	float _square_move_spd = 2.0f;
	glm::vec3 _square_color = { 0.2f, 0.3f, 0.8f };

	Pangolin::OrthographicCameraController _camera_controller;
};