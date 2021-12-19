#include "window.h"

#include "log.h"

#include "window_events.h"
#include "key_events.h"
#include "mouse_events.h"

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

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowProps data = *(WindowProps*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event((uint32_t)width, (uint32_t)height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowProps data = *(WindowProps*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,
		                                int key,
		                                int scancode,
		                                int action,
		                                int mods) {
			WindowProps data = *(WindowProps*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_REPEAT:
				case GLFW_PRESS:
				{
					KeyPressedEvent keyPressedEvent(key);
					data.EventCallback(keyPressedEvent);
					break;
				}
				case GLFW_RELEASE: 
				{
					KeyReleasedEvent keyReleasedEvent(key);
					data.EventCallback(keyReleasedEvent);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window,
		                                        int button,
		                                        int action,
		                                        int mods) {
			WindowProps data = *(WindowProps*)glfwGetWindowUserPointer(window);

			switch(action)
			{
				case GLFW_REPEAT:
				case GLFW_PRESS: 
				{
					MouseButtonPressedEvent mouseButtonPressed(button);
					data.EventCallback(mouseButtonPressed);
					break;
				}
				case GLFW_RELEASE: 
				{
					MouseButtonReleasedEvent mouseButtonReleased(button);
					data.EventCallback(mouseButtonReleased);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowProps data = *(WindowProps*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event(xPos, yPos);
			data.EventCallback(event);
		});

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