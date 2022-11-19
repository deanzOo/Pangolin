#include "plpch.h"
#include "Texture2D.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"

namespace Pangolin {
	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return create_ref<OpenGLTexture2D>(width, height);
		}

		return nullptr;
	}
	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			PL_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return create_ref<OpenGLTexture2D>(path);
		}

		return nullptr;
	}
}