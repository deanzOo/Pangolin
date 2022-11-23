#pragma once

#include "Pangolin/Renderer/Buffers/VertexBuffer.h"

namespace Pangolin {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const BufferLayout& get_layout() const override { return m_layout; };
		inline virtual void set_layout(const BufferLayout& layout) override { m_layout = layout; }

		virtual void set_data(const void* data, uint32_t size) override;
	private:
		uint32_t _rendrer_id;
		BufferLayout m_layout;
	};
}