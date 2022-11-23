#include "plpch.h"
#include "OpenGLIndexBuffer.h"

#include "glad/glad.h"

namespace Pangolin {
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_count(count)
	{
		PL_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &_rendrer_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendrer_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		PL_PROFILE_FUNCTION();

		glDeleteBuffers(1, &_rendrer_id);
	}

	void OpenGLIndexBuffer::bind() const
	{
		PL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendrer_id);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		PL_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
