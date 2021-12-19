#pragma once

#include <string>
#include <functional>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "event.h"

namespace Spirit
{
	using EventCallbackFn = std::function<void(Event&)>;

	struct WindowProps
	{
		uint32_t Width, Height;
		std::string Title;
		EventCallbackFn EventCallback;

		WindowProps(const std::string& title = "Spirit Window",
		            uint32_t width = 800,
		            uint32_t height = 600)
			: Width(width), Height(height), Title(title) {}
	};

	class Window
	{
	public:
		Window(const WindowProps& data);
		~Window();

		void OnUpdate();

		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		GLFWwindow& GetNativeWindow() { return *m_Window; }

	private:
		GLFWwindow* m_Window;
		WindowProps m_Data;
	};
}