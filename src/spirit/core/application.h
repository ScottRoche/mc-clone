#pragma once

#include <memory>

#include "window.h"
#include "window_events.h"

namespace Spirit
{
	class Application
	{
	public:
		Application();
		~Application();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

		void OnEvent(Event& e);
		void Run();

	private:
		void OnWindowResize(WindowResizeEvent& e);
		void OnWindowClose(WindowCloseEvent& e);

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
	};
}