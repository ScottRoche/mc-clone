#pragma once

#include "engine/sprtpch.h"

#include "window.h"
#include "window_events.h"
#include "layer_stack.h"

namespace Spirit
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		void OnEvent(Event& e);
		void Run();

	protected:
		LayerStack m_LayerStack;

	private:
		void OnWindowResize(WindowResizeEvent& e);
		void OnWindowClose(WindowCloseEvent& e);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}