#include "gepch.h"
#include "Shader.h"

#include "GamEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/Shaders/OpenGLShader.h"

namespace GamEngine {
	Shader* Shader::create(const std::string& vertex_src, const std::string& fragment_src)
    {
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertex_src, fragment_src);
		}

		return nullptr;
    }
}
