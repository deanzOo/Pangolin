#pragma once

#include "Pangolin/Core/Core.h"

namespace Pangolin {
	struct FrameBufferSpecification {
		uint32_t width, height;
		uint32_t samples;

		bool swap_chain_target = false;
	};

	class FrameBuffer {
	public:
		virtual ~FrameBuffer() = default;
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t get_color_attachment_renderer_id() const = 0;

		virtual FrameBufferSpecification& get_specification() = 0;
		virtual const FrameBufferSpecification& get_specification() const = 0;

		static Ref<FrameBuffer> create(const FrameBufferSpecification spec);
	};
}