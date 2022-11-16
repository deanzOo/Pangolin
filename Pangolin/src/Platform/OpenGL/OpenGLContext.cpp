#include "plpch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pangolin {
	OpenGLContext::OpenGLContext(GLFWwindow* handle) : m_handle(handle) {
		PL_CORE_ASSERT(m_handle, "Window handle is null!");
	}
	
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_handle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		std::string gl_verion = std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		std::string gl_renderer = std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		
		PL_CORE_ASSERT(status, "Failed to initialize OpenGL context!");
		PL_CORE_INFO("OpenGL Info:");
		PL_CORE_INFO("    Vendor: {0}", gl_verion);
		PL_CORE_INFO("    Renderer: {0}", gl_renderer);
		PL_CORE_INFO("    Version: {0}.{1}", GLVersion.major, GLVersion.minor);

		#ifdef PL_ENABLE_ASSERTS
			int version_major, version_minor;
			glGetIntegerv(GL_MAJOR_VERSION, &version_major);
			glGetIntegerv(GL_MINOR_VERSION, &version_minor);

			PL_CORE_ASSERT(version_major > 4 || (version_major == 4 && version_minor >= 5), "Pangolin requires OpenGL version >= 4.5 !");
		#endif
	}

	void OpenGLContext::swap_buffers()
	{
		glfwSwapBuffers(m_handle);
	}
}