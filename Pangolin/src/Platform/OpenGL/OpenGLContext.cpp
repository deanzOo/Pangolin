#include "gepch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pangolin {
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

		#ifdef GE_ENABLE_ASSERTS
			int version_major, version_minor;
			glGetIntegerv(GL_MAJOR_VERSION, &version_major);
			glGetIntegerv(GL_MINOR_VERSION, &version_minor);

			GE_CORE_ASSERT(version_major > 4 || (version_major == 4 && version_minor >= 5), "Pangolin requires OpenGL version >= 4.5 !");
		#endif
	}

	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(m_handle);
	}
}