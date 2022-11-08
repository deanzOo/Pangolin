#include "gepch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GamEngine {
	RendererAPI* RenderCommand::renderer_api = new OpenGLRendererAPI();
}