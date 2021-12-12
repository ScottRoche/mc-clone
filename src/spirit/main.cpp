#include <iostream>

#include <glm.hpp>

#include "core/log.h"
#include "core/window.h"

#include "renderer/renderer.h"
#include "renderer/camera.h"

#include "event.h"
#include "window_events.h"
#include "key_events.h"
#include "mouse_events.h"

static float s_SampleVerts[] = {
	// Front
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-right
	
	// Back
	-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-left
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-right

	// Left
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-top
	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-front
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-back
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right

	// Right
	 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-top
	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-front
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-back
	 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right

	// Top
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // front-top
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-front
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-back
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-right

	// Bottom
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // front-top
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-front
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-back
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-right
};

static bool s_IsRunning = true;

static void OnWindowResize(Spirit::WindowResizeEvent& e)
{
	Spirit::Renderer::SetViewportSize(e.GetWidth(), e.GetHeight());
}

static void OnWindowClose(Spirit::WindowCloseEvent& e)
{
	s_IsRunning = false;
}

static void OnKeyPressed(Spirit::KeyPressedEvent& e)
{
	LOG_DEBUG("Key Pressed: {:d}", e.GetKey());
}

static void OnKeyReleased(Spirit::KeyReleasedEvent& e)
{
	LOG_DEBUG("Key Released: {:d}", e.GetKey());
}

static void OnButtonPressed(Spirit::MouseButtonPressedEvent& e)
{
	LOG_DEBUG("Mouse Button Pressed: {:d}", e.GetButton());
}

static void OnButtonReleased(Spirit::MouseButtonReleasedEvent& e)
{
	LOG_DEBUG("Mouse Button Released: {:d}", e.GetButton());
}

static void OnMouseMoved(Spirit::MouseMovedEvent& e)
{
	LOG_DEBUG("Mouse Position: {:f}, {:f}", e.GetX(), e.GetY());
}

static void OnEvent(Spirit::Event& e)
{
	Spirit::EventDispatcher dispatcher(e);

	dispatcher.Dispatch<Spirit::WindowResizeEvent>(OnWindowResize);
	dispatcher.Dispatch<Spirit::WindowCloseEvent>(OnWindowClose);
	dispatcher.Dispatch<Spirit::KeyPressedEvent>(OnKeyPressed);
	dispatcher.Dispatch<Spirit::KeyReleasedEvent>(OnKeyReleased);
	dispatcher.Dispatch<Spirit::MouseButtonPressedEvent>(OnButtonPressed);
	dispatcher.Dispatch<Spirit::MouseButtonReleasedEvent>(OnButtonReleased);
	dispatcher.Dispatch<Spirit::MouseMovedEvent>(OnMouseMoved);
}

int main(int argc, char *argv[])
{
	Spirit::Log::Init();
	LOG_INFO("Logger Initalised");

	Spirit::Window window(Spirit::WindowProps("Minecraft Clone"));
	window.SetEventCallback(OnEvent);

	Spirit::Camera camera(45.0f, glm::vec2(800.0f, 600.0f), 0.1f, 100.0f);
	camera.SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	camera.SetYaw(20.0f);

	Spirit::Renderer::Init();
	/* This is only temporary. There should be no GetWindowHandle and telling the
	 * window should tell the application in a callback that it has closed. */
	while (s_IsRunning)
	{
		static float lastFrameTs = 0;

		float ts = glfwGetTime();
		float deltaTime = ts - lastFrameTs;
		lastFrameTs = ts;

		float s_EditVerts[sizeof(s_SampleVerts)/sizeof(float)];
		memcpy(s_EditVerts, s_SampleVerts, sizeof(s_SampleVerts));

		window.OnUpdate();

		camera.SetYaw(200.0f * deltaTime);

		Spirit::Renderer::BeginScene(camera);

		Spirit::Renderer::Submit(s_SampleVerts, sizeof(s_SampleVerts));

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < sizeof(s_EditVerts) / sizeof(float); j += 6)
			{
				s_EditVerts[j] -= 2.0f;
			}
			Spirit::Renderer::Submit(s_EditVerts, sizeof(s_EditVerts));
		}
		Spirit::Renderer::EndScene();
	}

	Spirit::Renderer::Deinit();
	return 0;
}