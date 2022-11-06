#include "gepch.h"
#include "VertexArray.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Arrays/OpenGLVertexArray.h"

namespace GamEngine {
	VertexArray* VertexArray::create()
	{
		switch (Renderer::get_api()) {
		case RendererAPI::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		return nullptr;
	}
}