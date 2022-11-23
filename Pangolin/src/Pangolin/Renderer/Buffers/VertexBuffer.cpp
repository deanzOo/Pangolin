#include "plpch.h"
#include "VertexBuffer.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace Pangolin {

	Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
	{
		RendererAPI::API api = Renderer::get_api();
		switch (api) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return create_ref<OpenGLVertexBuffer>(size);
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		RendererAPI::API api = Renderer::get_api();
		switch (api) {
		case RendererAPI::API::None: 
			PL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return create_ref<OpenGLVertexBuffer>(vertices, size);
		}

		PL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}