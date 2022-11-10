#pragma once

#include "GamEngine/Core/Layer.h"
#include <GamEngine/Renderer/Shaders/Shader.h>
#include <GamEngine/Renderer/Arrays/VertexArray.h>
#include "GamEngine/Renderer/OrthographicCamera.h"

class ExampleLayer : public GamEngine::Layer {
public:
	ExampleLayer();

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update() override;
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

	GamEngine::OrthographicCamera _camera;
};