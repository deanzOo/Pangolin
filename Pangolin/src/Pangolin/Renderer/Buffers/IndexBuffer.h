#pragma once

#include "Buffer.h"

namespace Pangolin {
	class IndexBuffer : public Buffer {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t get_count() const = 0;
		virtual void set_data(const void* data, uint32_t size) = 0;

		static Ref<IndexBuffer> create(uint32_t* indices, uint32_t size);
	};
}
