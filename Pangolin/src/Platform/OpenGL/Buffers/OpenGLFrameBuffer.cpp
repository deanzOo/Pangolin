#include "plpch.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Pangolin {
	OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferSpecification spec)
		: _spec(spec)
	{
		invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &_renderer_id);
	}

	void OpenGLFrameBuffer::invalidate()
	{
		glCreateFramebuffers(1, &_renderer_id);
		
		glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);

		glCreateTextures(GL_TEXTURE_2D, 1,  &_color_attachment);
		glBindTexture(GL_TEXTURE_2D, _color_attachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _spec.width, _spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_attachment, 0);
		
		glCreateTextures(GL_TEXTURE_2D, 1, &_depth_attachment);
		glBindTexture(GL_TEXTURE_2D, _depth_attachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _spec.width, _spec.height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _spec.width, _spec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depth_attachment, 0);

		PL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void OpenGLFrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
	}

	void OpenGLFrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}