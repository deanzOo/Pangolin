#include "gepch.h"
#include "App.h"
#include "Input.h"
#include <glad/glad.h>
#include <GamEngine/Renderer/Buffers/BufferLayout.h>

namespace GamEngine {

	App* App::instance = nullptr;

	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float: return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3: return GL_FLOAT;
			case ShaderDataType::Mat4: return GL_FLOAT;
			case ShaderDataType::Int: return GL_INT;
			case ShaderDataType::Int2: return GL_INT;
			case ShaderDataType::Int3: return GL_INT;
			case ShaderDataType::Int4: return GL_INT;
			case ShaderDataType::Bool: return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	App::App()
	{
		GE_CORE_ASSERT(!instance, "App already exists!");
		instance = this;

		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(GE_BIND_EVENT_FN(App::on_event));

		m_imgui_layer = new ImGuiLayer();
		push_overlay(m_imgui_layer);

		glGenVertexArrays(1, &m_vertex_array);
		glBindVertexArray(m_vertex_array);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		m_vertex_buffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "i_position"}
			};
			m_vertex_buffer->set_layout(layout);
		}
		uint32_t index = 0;
		const auto& layout = m_vertex_buffer->get_layout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index++,
				element.get_component_count(),
				ShaderDataTypeToGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.get_stride(),
				(const void*)element.offset
			);
		}

		uint32_t indices[3] = { 0, 1, 2 };
		m_index_buffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

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
			glBindVertexArray(m_vertex_array);
			glDrawElements(GL_TRIANGLES, m_index_buffer->get_count(), GL_UNSIGNED_INT, nullptr);

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