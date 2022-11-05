#pragma once

#include "GamEngine/Renderer/Buffers/IndexBuffer.h"

namespace GamEngine {
	class OpenGLIndexBuffer: public IndexBuffer{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t get_count() const { return m_count; }
	private:
		uint32_t m_rendrer_id;
		uint32_t m_count;
	};
}