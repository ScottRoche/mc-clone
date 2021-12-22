#include "application.h"

#include "log.h"
#include "input.h"
#include "key_codes.h"

#include "renderer/renderer.h"

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>


namespace Spirit
{
	Application* Application::s_Instance = nullptr;
	bool s_IsRunning = true;

	#define SPRT_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

	Application::Application()
	{
		Log::Init();
		LOG_INFO("Logger Initalised");

		s_Instance = this;
		m_Window = std::make_unique<Window>(WindowProps("Minecraft Clone"));
		m_Window->SetEventCallback(SPRT_BIND_FN(Application::OnEvent));

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Deinit();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Spirit::WindowResizeEvent>(SPRT_BIND_FN(Application::OnWindowResize));
		dispatcher.Dispatch<Spirit::WindowCloseEvent>(SPRT_BIND_FN(Application::OnWindowClose));
	}

	void Application::Run()
	{
		while(s_IsRunning)
		{
			static float lastFrame = 0.0f;
			float ts = glfwGetTime();
			float deltaTime = ts - lastFrame;
			lastFrame = ts;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);

			for (Layer *object : m_ObjectStack)
			{
				object->OnUpdate(deltaTime);
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::SetViewportSize(e.GetWidth(), e.GetHeight());
	}

	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		s_IsRunning = false;
	}
}