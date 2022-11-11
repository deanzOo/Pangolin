#pragma once

#include "GamEngine/Core/Layer.h"
#include "GamEngine/Core/Timestep.h"
#include <GamEngine/Renderer/Shaders/Shader.h>
#include <GamEngine/Renderer/Arrays/VertexArray.h>
#include "GamEngine/Renderer/OrthographicCamera.h"

class ExampleLayer : public GamEngine::Layer {
public:
	ExampleLayer();

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update(GamEngine::Timestep step) override;
	virtual void on_imgui_render() override;
	void on_event(GamEngine::Event& event) override;

private:
	bool on_key_pressed(GamEngine::KeyPressedEvent& event);

private:
	GamEngine::Ref<GamEngine::Shader> _flat_color_shader;

	GamEngine::Ref<GamEngine::VertexArray> _square_vertex_array;
	GamEngine::Ref<GamEngine::VertexBuffer> _square_vertex_buffer;
	GamEngine::Ref<GamEngine::IndexBuffer> _square_index_buffer;
	float _square_move_spd = 2.0f;
	glm::vec3 _square_color = { 0.2f, 0.3f, 0.8f };

	GamEngine::OrthographicCamera _camera;
	float _camera_move_spd = 2.0f;
	float _camera_rotate_spd = 45.0f;

};