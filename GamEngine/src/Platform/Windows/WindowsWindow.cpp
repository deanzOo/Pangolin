#include "gepch.h"
#include "WindowsWindow.h"

#include "GamEngine/Events/KeyEvent.h"
#include "GamEngine/Events/MouseEvent.h"
#include "GamEngine/Events/AppEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace GamEngine {

	static bool GLFWInitialized = false;

	Window* Window::create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props) {
		m_data.title = props.m_title;
		m_data.width = props.m_width;
		m_data.height = props.m_height;

		GE_CORE_INFO("Creating window {0} ({1}, {2})", props.m_title, props.m_width, props.m_height);
		
		if (!GLFWInitialized) {
			int success = glfwInit();
			GE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback([](int error_code, const char* description) {
				GE_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
			});
			GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.m_width, (int)props.m_height, m_data.title.c_str(), nullptr, nullptr);
		
		m_context = new OpenGLContext(m_window);
		m_context->init();
		
		glfwSetWindowUserPointer(m_window, &m_data);
		set_vsync(true);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.event_callback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.event_callback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(key, scancode, mods, 0);
				data.event_callback(event);
				break; 
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key, scancode, mods);
				data.event_callback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, scancode, mods, 1);
				data.event_callback(event);
				break;
			}
			}
		});


		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.event_callback(event);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button, mods);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button, mods);
				data.event_callback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_offset, double y_offset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)x_offset, (float)y_offset);
			data.event_callback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_position, double y_position) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_position, (float)y_position);
			data.event_callback(event);
		});
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::on_update() {
		glfwPollEvents();
		m_context->swap_buffers();
	}

	void WindowsWindow::set_vsync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}

}