#include "window.h"

#include "log.h"

namespace Spirit
{
	static unsigned int s_WindowCount = 0;

	Window::Window(const WindowProps& data)
	{
		if (s_WindowCount == 0)
		{
			if (!glfwInit())
			{
				LOG_FATAL("GLFW failed to initalise.");
				return;
			}
		}

		m_Data = data;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Window = glfwCreateWindow(m_Data.Width,
		                            m_Data.Height,
		                            m_Data.Title.c_str(),
		                            NULL,
		                            NULL);

		if (m_Window == nullptr)
		{
			LOG_ERROR("GLFW failed to create window");
			return;
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("GLAD failed to initalise");
			return;
		}

		s_WindowCount++;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		s_WindowCount--;
		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}