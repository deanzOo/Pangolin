#include "plpch.h"
#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"

namespace Pangolin {
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		PL_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_rendrer_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendrer_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		PL_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_rendrer_id);
	}
	void OpenGLVertexBuffer::bind() const
	{
		PL_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_rendrer_id);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		PL_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
