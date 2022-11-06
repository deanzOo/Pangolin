#include "gepch.h"
#include "VertexBuffer.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace GamEngine {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::None: 
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}