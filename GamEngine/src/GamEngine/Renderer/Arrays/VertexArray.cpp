#include "gepch.h"
#include "VertexArray.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Arrays/OpenGLVertexArray.h"

namespace GamEngine {
	VertexArray* VertexArray::create()
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		return nullptr;
	}
}