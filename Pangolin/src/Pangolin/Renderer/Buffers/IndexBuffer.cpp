#include "gepch.h"
#include "IndexBuffer.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"

namespace Pangolin {
	Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
	}
}