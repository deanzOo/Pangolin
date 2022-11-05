#pragma once

#include "GamEngine/Renderer/Buffers/VertexBuffer.h"

namespace GamEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		uint32_t m_rendrer_id;
	};
}