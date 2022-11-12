#include "gepch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace GamEngine {

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

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &_renderer_id);
		bind();
	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(_renderer_id);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		GE_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Vertex buffer has no layout!");
		
		bind();
		vertex_buffer->bind();

		uint32_t index = 0;
		const auto& layout = vertex_buffer->get_layout();
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
		_vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
	{
		bind();
		index_buffer->bind();

		_index_buffer = index_buffer;
	}

}
