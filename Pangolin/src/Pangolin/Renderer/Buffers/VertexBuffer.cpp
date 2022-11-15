#include "gepch.h"
#include "VertexBuffer.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace Pangolin {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		RendererAPI::API api = Renderer::get_api();
		switch (api) {
		case RendererAPI::API::None: 
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}