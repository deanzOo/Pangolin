#pragma once

#include "GamEngine/Core/Layer.h"
#include <GamEngine/Renderer/Shaders/Shader.h>
#include <GamEngine/Renderer/Arrays/VertexArray.h>

class ExampleLayer : public GamEngine::Layer {
public:
	ExampleLayer();

	virtual void on_attach() override;
	virtual void on_detach() override;
	virtual void on_update() override;
	void on_event(GamEngine::Event& event) override;

private:
	std::shared_ptr<GamEngine::Shader> m_shader;

	std::shared_ptr<GamEngine::VertexArray> m_triangle_vertex_array;
	std::shared_ptr<GamEngine::VertexBuffer> m_triangle_vertex_buffer;
	std::shared_ptr<GamEngine::IndexBuffer> m_triangle_index_buffer;

	std::shared_ptr<GamEngine::VertexArray> m_square_vertex_array;
	std::shared_ptr<GamEngine::VertexBuffer> m_square_vertex_buffer;
	std::shared_ptr<GamEngine::IndexBuffer> m_square_index_buffer;
};