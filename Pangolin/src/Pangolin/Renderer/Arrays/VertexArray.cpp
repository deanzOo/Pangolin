#include "gepch.h"
#include "VertexArray.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Arrays/OpenGLVertexArray.h"

namespace Pangolin {
	VertexArray* VertexArray::create()
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		return nullptr;
	}
}