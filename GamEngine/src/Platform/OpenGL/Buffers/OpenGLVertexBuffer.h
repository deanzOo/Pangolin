#pragma once

#include "GamEngine/Renderer/Buffers/VertexBuffer.h"

namespace GamEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const BufferLayout& get_layout() const override { return m_layout; };
		inline virtual void set_layout(const BufferLayout& layout) override { m_layout = layout; }
	private:
		uint32_t m_rendrer_id;
		BufferLayout m_layout;
	};
}