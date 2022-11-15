#pragma once
#include <Pangolin/Renderer/Buffers/BufferLayout.h>

namespace Pangolin {
	class Buffer {
	public:
		virtual ~Buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& get_layout() const = 0;
		virtual void set_layout(const BufferLayout& layout) = 0;
	};
}