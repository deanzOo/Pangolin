#pragma once

#include "Pangolin/Renderer/Buffers/IndexBuffer.h"

namespace Pangolin {
	class OpenGLIndexBuffer: public IndexBuffer{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		inline virtual const BufferLayout& get_layout() const override { return m_layout; };
		inline virtual void set_layout(const BufferLayout& layout) override { m_layout = layout; }
		inline virtual void set_data(const void* data, uint32_t size) {};

		virtual uint32_t get_count() const { return m_count; }
	private:
		uint32_t _rendrer_id;
		BufferLayout m_layout;
		uint32_t m_count;
	};
}