#include "gepch.h"
#include "Shader.h"

#include "Pangolin/Renderer/Renderer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

namespace Pangolin {
	Ref<Shader> Shader::create(const std::string& path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
		}

		return nullptr;
	}

	Ref<Shader> Shader::create(const std::string& name, const std::string& path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, path);
		}

		return nullptr;
	}
}
