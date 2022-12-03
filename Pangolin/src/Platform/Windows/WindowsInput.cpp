#include "plpch.h"

#include "Pangolin/Core/Input/Input.h"

#include "GLFW/glfw3.h"

#include "Pangolin/Core/App/App.h"

namespace Pangolin {
	bool Input::is_key_pressed(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());

		int status = glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}
	bool Input::is_mouse_button_pressed(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());

		int status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}
	std::pair<float, float> Input::get_mouse_position()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return std::pair<float, float>((float)x, (float)y);
	}
	float Input::get_mouse_x()
	{
		return get_mouse_position().first;
	}
	float Input::get_mouse_y()
	{
		return get_mouse_position().second;
	}
}