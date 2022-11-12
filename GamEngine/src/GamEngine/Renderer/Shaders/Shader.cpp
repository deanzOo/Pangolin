#include "gepch.h"
#include "Shader.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

namespace GamEngine {
	Shader* Shader::create(const std::string& path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(path);
		}

		return nullptr;
	}
}
