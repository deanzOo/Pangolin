#include "gepch.h"
#include "Texture2D.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

namespace GamEngine {
	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		return nullptr;
	}
}