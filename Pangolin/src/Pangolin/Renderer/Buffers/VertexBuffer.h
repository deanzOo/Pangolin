#pragma once

#include "Buffer.h"

namespace Pangolin {
	class VertexBuffer : public Buffer {
	public:
		static Ref<VertexBuffer> create(uint32_t size);
		static Ref<VertexBuffer> create(float* vertices, uint32_t size);
	};
}