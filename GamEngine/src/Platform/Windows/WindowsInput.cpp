#include "gepch.h"

#include "WindowsInput.h"

#include "GLFW/glfw3.h"

#include "GamEngine/Core/App.h"

namespace GamEngine {
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::is_key_pressed_impl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());

		int status = glfwGetKey(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}
	bool WindowsInput::is_mouse_button_pressed_impl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());

		int status = glfwGetMouseButton(window, button);
		return status == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::get_mouse_position_impl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(App::get().get_window().get_native_window());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return std::pair<float, float>((float)x, (float)y);
	}
	float WindowsInput::get_mouse_x_impl()
	{
		return get_mouse_position_impl().first;
	}
	float WindowsInput::get_mouse_y_impl()
	{
		return get_mouse_position_impl().second;
	}
}