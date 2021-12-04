#pragma once

#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Spirit
{
	struct WindowProps
	{
		uint32_t Width, Height;
		std::string Title;

		WindowProps(const std::string& title = "Spirit Window",
		            uint32_t width = 800,
		            uint32_t height = 600)
			: Width(width), Height(height), Title(title)
		{
		}
	};

	class Window
	{
	public:
		Window(const WindowProps& data);
		~Window();

		void OnUpdate();

		inline GLFWwindow* GetWindowHandle() const { return m_Window; }

	private:
		GLFWwindow* m_Window;
		WindowProps m_Data;
	};
}