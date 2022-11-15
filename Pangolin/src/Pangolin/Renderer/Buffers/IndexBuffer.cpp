#include "gepch.h"
#include "IndexBuffer.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"

namespace Pangolin {
	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		return nullptr;
	}
}