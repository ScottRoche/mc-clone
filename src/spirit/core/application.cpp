#include "application.h"

#include "log.h"
#include "input.h"
#include "key_codes.h"

#include "renderer/renderer.h"

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>


namespace Spirit
{
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
		// Camera camera(45.0f, glm::vec2(800.0f, 600.0f), 0.1f, 100.0f);
		// glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		// camera.SetPosition(position);
		// float cameraSpeed = 1.0f;

		// float lastMouseX = 400.0f;
		// float lastMouseY = 300.0f;

		while(s_IsRunning)
		{
			static float lastFrame = 0.0f;
			float ts = glfwGetTime();
			float deltaTime = ts - lastFrame;
			lastFrame = ts;

			for (Object *object : m_ObjectStack)
			{
				object->OnUpdate(deltaTime);
			}

			m_Window->OnUpdate();
		}

		// 	if (Input::IsKeyPressed(KeyCode::W))
		// 	{
		// 		position += camera.GetForwardVector() * (cameraSpeed * deltaTime);
		// 		camera.SetPosition(position);
		// 	}
			
		// 	if (Input::IsKeyPressed(KeyCode::S))
		// 	{
		// 		position -= camera.GetForwardVector() * (cameraSpeed * deltaTime);
		// 		camera.SetPosition(position);
		// 	}

		// 	if (Input::IsKeyPressed(KeyCode::D))
		// 	{
		// 		position += camera.GetRightVector() * (cameraSpeed * deltaTime);
		// 		camera.SetPosition(position);
		// 	}

		// 	if (Input::IsKeyPressed(KeyCode::A))
		// 	{
		// 		position -= camera.GetRightVector() * (cameraSpeed * deltaTime);
		// 		camera.SetPosition(position);
		// 	}

		// 	auto[mouseX, mouseY] = Input::GetMousePos();
		// 	LOG_DEBUG("{:f}, {:f}", (float)mouseX, (float)mouseY);

		// 	camera.AddYaw(((float)mouseX - lastMouseX) * 0.1f);
		// 	camera.AddPitch((lastMouseY - (float)mouseY) * 0.1f);
		// 	lastMouseX = (float)mouseX;
		// 	lastMouseY = (float)mouseY;

		// 	Renderer::BeginScene(camera);
		// 	Renderer::Submit(s_SampleVerts, sizeof(s_SampleVerts));
		// 	Renderer::EndScene();
		// }

		// Renderer::Deinit();
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