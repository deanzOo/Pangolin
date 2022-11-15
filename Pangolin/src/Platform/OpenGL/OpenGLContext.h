#pragma once

#include "Pangolin/Renderer/Context.h"

struct GLFWwindow;

namespace Pangolin {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(GLFWwindow* handle);

		virtual void init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* m_handle;
	};
}