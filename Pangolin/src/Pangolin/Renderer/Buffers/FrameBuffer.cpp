#include "plpch.h"
#include "FrameBuffer.h"
#include "Platform/OpenGL/Buffers/OpenGLFrameBuffer.h"
#include "Pangolin/Renderer/Renderer.h"

namespace Pangolin {
	Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification spec)
	{
		RendererAPI::API api = Renderer::get_api();
		switch (api) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return create_ref<OpenGLFrameBuffer>(spec);
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}