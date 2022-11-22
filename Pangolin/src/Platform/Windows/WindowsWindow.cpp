#include "plpch.h"
#include "WindowsWindow.h"

#include "Pangolin/Events/KeyEvent.h"
#include "Pangolin/Events/MouseEvent.h"
#include "Pangolin/Events/AppEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace Pangolin {

	static bool GLFWInitialized = false;

	Scope<Window> Window::create(const WindowProps& props) {
		return create_scope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		PL_PROFILE_FUNCTION();
		
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props) {
		PL_PROFILE_FUNCTION();

		_data.title = props._title;
		_data.width = props._width;
		_data.height = props._height;

		PL_CORE_INFO("Creating window {0} ({1}, {2})", props._title, props._width, props._height);
		
		if (!GLFWInitialized) {
			PL_PROFILE_SCOPE("WindowsWindow::glfwInit");
			int success = glfwInit();
			PL_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback([](int error_code, const char* description) {
				PL_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
			});
			GLFWInitialized = true;
		}

		{
			PL_PROFILE_SCOPE("WindowsWindow::glfwCreateWindow");
			_window = glfwCreateWindow((int)props._width, (int)props._height, _data.title.c_str(), nullptr, nullptr);
		}
		
		_context = new OpenGLContext(_window);
		_context->init();
		
		glfwSetWindowUserPointer(_window, &_data);
		set_vsync(true);

		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.event_callback(event);
		});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.event_callback(event);
		});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
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


		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int codepoint) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.event_callback(event);
		});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
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

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double x_offset, double y_offset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)x_offset, (float)y_offset);
			data.event_callback(event);
		});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x_position, double y_position) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_position, (float)y_position);
			data.event_callback(event);
		});
	}

	void WindowsWindow::shutdown() {
		PL_PROFILE_FUNCTION();
		
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::on_update() {
		PL_PROFILE_FUNCTION();

		{
			PL_PROFILE_SCOPE("WindwosWindow::on_update-glfwPollEvents");

			glfwPollEvents();
		}
		{
			PL_PROFILE_SCOPE("WindwosWindow::on_update-context::swap_buffers q");

			_context->swap_buffers();
		}
	}

	void WindowsWindow::set_vsync(bool enabled) {
		PL_PROFILE_FUNCTION();
		
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.vsync = enabled;
	}

}