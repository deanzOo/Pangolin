#pragma once

#include "Pangolin/Renderer/Buffers/FrameBuffer.h"

namespace Pangolin {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(FrameBufferSpecification spec);
		virtual ~OpenGLFrameBuffer();

		void invalidate();

		virtual void bind() override;
		virtual void unbind() override;

		inline virtual uint32_t get_color_attachment_renderer_id() const override { return _color_attachment; }

		inline virtual FrameBufferSpecification& get_specification() override { return _spec; }
		inline virtual const FrameBufferSpecification& get_specification() const override { return _spec; }
	private:
		uint32_t _renderer_id;
		uint32_t _color_attachment, _depth_attachment;
		FrameBufferSpecification _spec;
	};
}