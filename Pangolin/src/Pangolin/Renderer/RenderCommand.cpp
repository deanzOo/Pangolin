#include "gepch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Pangolin {
	RendererAPI* RenderCommand::_renderer_api = new OpenGLRendererAPI();
}