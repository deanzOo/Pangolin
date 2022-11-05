#pragma once

#include "Buffer.h"

namespace GamEngine {
	class VertexBuffer : public Buffer {
	public:
		virtual ~VertexBuffer() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		static VertexBuffer* create(float* vertices, uint32_t size);
	};
}