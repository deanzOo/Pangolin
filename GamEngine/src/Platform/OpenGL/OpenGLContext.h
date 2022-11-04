#pragma once

#include "GamEngine/Renderer/Context.h"

struct GLFWwindow;

namespace GamEngine {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(GLFWwindow* handle);

		virtual void init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* m_handle;
	};
}