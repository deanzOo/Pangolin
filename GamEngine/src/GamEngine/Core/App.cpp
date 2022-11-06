#include "gepch.h"
#include "App.h"
#include "Input.h"
#include <glad/glad.h>
#include <GamEngine/Renderer/Buffers/BufferLayout.h>

namespace GamEngine {

	App* App::instance = nullptr;

	App::App()
	{
		GE_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(GE_BIND_EVENT_FN(App::on_event));

		m_imgui_layer = new ImGuiLayer();
		push_overlay(m_imgui_layer);

		m_triangle_vertex_array.reset(VertexArray::create());

		float verticesTriangle[3 * 3] = {
			-0.5f, -0.5f, 1.0f,
			0.5f, -0.5f, 1.0f,
			0.0f, 0.5f, 1.0f
		};
		m_triangle_vertex_buffer.reset(VertexBuffer::create(verticesTriangle, sizeof(verticesTriangle)));

		{
			BufferLayout layout_triangle = {
				{ ShaderDataType::Float3, "i_position"}
			};
			m_triangle_vertex_buffer->set_layout(layout_triangle);
		}
		m_triangle_vertex_array->add_vertex_buffer(m_triangle_vertex_buffer);

		uint32_t indicesTriangle[3] = { 0, 1, 2 };
		m_triangle_index_buffer.reset(IndexBuffer::create(indicesTriangle, sizeof(indicesTriangle) / sizeof(uint32_t)));
		m_triangle_vertex_array->set_index_buffer(m_triangle_index_buffer);

		m_triangle_vertex_array->unbind();


		m_square_vertex_array.reset(VertexArray::create());

		float verticesSquare[3 * 4] = {
			-0.2f, -0.2f, 0.0f,
			-0.2f, 0.2f, 0.0f,
			0.2f, 0.2f, 0.0f,
			0.2f, -0.2f, 0.0f
		};
		m_square_vertex_buffer.reset(VertexBuffer::create(verticesSquare, sizeof(verticesSquare)));

		{
			BufferLayout layoutSquare = {
				{ ShaderDataType::Float3, "i_position"}
			};
			m_square_vertex_buffer->set_layout(layoutSquare);
		}
		m_square_vertex_array->add_vertex_buffer(m_square_vertex_buffer);

		uint32_t indicesSquare[6] = { 0, 1, 2, 2, 3, 0 };
		m_square_index_buffer.reset(IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
		m_square_vertex_array->set_index_buffer(m_square_index_buffer);

		m_square_vertex_array->unbind();

		std::string vertex_src = R"(
			#version 330 core

			layout(location = 0) in vec3 i_position;

			out vec3 o_position;

			void main() {
				o_position = i_position * 0.5 + 0.5;
				gl_Position = vec4(i_position, 1.0);
			}
		)";

		std::string fragment_src = R"(
			#version 330 core

			layout(location = 0) out vec4 o_color;

			in vec3 o_position;

			void main() {
				o_color = vec4(o_position, 1.0);
			}
		)";

		m_shader.reset(Shader::create(vertex_src, fragment_src));
	}

	App::~App()
	{
	}

	void App::on_event(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(App::on_window_close));

		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); ) {
			(*--it)->on_event(e);
			if (e.is_handled())
				break;
		}
	}

	void App::push_layer(Layer* layer)
	{
		m_layer_stack.push_layer(layer);
		layer->on_attach();
	}

	void App::push_overlay(Layer* layer)
	{
		m_layer_stack.push_overlay(layer);
		layer->on_attach(); 
	}

	bool App::on_window_close(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	void App::run() {
		while (running) {
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->bind();
			m_triangle_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, m_triangle_index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

			m_square_vertex_array->bind();
			glDrawElements(GL_TRIANGLES, m_square_index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_layer_stack)
				layer->on_update();

			m_imgui_layer->begin();
			for (Layer* layer : m_layer_stack)
				layer->on_imgui_render();
			m_imgui_layer->end();

			m_window->on_update();
		}
	}
}