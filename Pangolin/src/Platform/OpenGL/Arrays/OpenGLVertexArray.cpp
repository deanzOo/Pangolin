#include "plpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Pangolin {

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

		PL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		PL_PROFILE_FUNCTION();
		
		glCreateVertexArrays(1, &_renderer_id);
	}
	void OpenGLVertexArray::bind() const
	{
		PL_PROFILE_FUNCTION();
		
		glBindVertexArray(_renderer_id);
	}

	void OpenGLVertexArray::unbind() const
	{
		PL_PROFILE_FUNCTION();
		
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		PL_PROFILE_FUNCTION();
		
		PL_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Vertex buffer has no layout!");
		
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
				(const void*)(size_t)element.offset
			);
		}
		_vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer>& index_buffer)
	{
		PL_PROFILE_FUNCTION();
		
		bind();
		index_buffer->bind();

		_index_buffer = index_buffer;
	}

}
