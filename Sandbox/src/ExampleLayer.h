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
	void on_event(GamEngine::Event& event) override;

private:
	bool on_key_pressed(GamEngine::KeyPressedEvent& event);

private:
	std::shared_ptr<GamEngine::Shader> _shader;

	std::shared_ptr<GamEngine::VertexArray> _triangle_vertex_array;
	std::shared_ptr<GamEngine::VertexBuffer> _triangle_vertex_buffer;
	std::shared_ptr<GamEngine::IndexBuffer> _triangle_index_buffer;

	std::shared_ptr<GamEngine::VertexArray> _square_vertex_array;
	std::shared_ptr<GamEngine::VertexBuffer> _square_vertex_buffer;
	std::shared_ptr<GamEngine::IndexBuffer> _square_index_buffer;
	glm::vec3 _square_position;
	float _square_move_spd = 2.0f;

	GamEngine::OrthographicCamera _camera;
	float _camera_move_spd = 2.0f;
	float _camera_rotate_spd = 45.0f;

};