#include "gepch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GamEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* handle) : m_handle(handle) {
		GE_CORE_ASSERT(m_handle, "Window handle is null!");
	}
	
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_handle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to initialize OpenGL context!");
		GE_CORE_INFO("OpenGL Info:");
		GE_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO("    Version: {0}.{1}", GLVersion.major, GLVersion.minor);
	}

	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(m_handle);
	}
}