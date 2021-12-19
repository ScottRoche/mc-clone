#include "input.h"

#include "application.h"
#include "log.h"

namespace Spirit
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		GLFWwindow& window = Application::Get().GetWindow().GetNativeWindow();
		return glfwGetKey(&window, (int)key) == GLFW_PRESS;
	}

	bool Input::IsButtonPressed(MouseButton button)
	{
		GLFWwindow& window = Application::Get().GetWindow().GetNativeWindow();
		return glfwGetMouseButton(&window, (int)button) == GLFW_PRESS;
	}

	std::tuple<float, float> Input::GetMousePos()
	{
		double xpos, ypos;
		GLFWwindow& window = Application::Get().GetWindow().GetNativeWindow();
		glfwGetCursorPos(&window, &xpos, &ypos);
		return std::tuple<float, float>{(float)xpos, (float)ypos};
	}
}