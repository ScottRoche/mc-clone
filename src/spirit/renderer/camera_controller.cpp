#include "camera_controller.h"

#include "core/log.h"

namespace Spirit
{
	CameraController::CameraController(std::shared_ptr<Camera> camera)
		: m_Camera(camera)
	{
		m_Position = m_Camera->GetPosition();
	}

	CameraController::~CameraController()
	{

	}

	void CameraController::OnUpdate(float deltaTime)
	{
		static float lastMouseX = 400, lastMouseY = 300;

		float cameraSpeed = 5.0f;

		if (Input::IsKeyPressed(KeyCode::W))
		{
			m_Position += m_Camera->GetForwardVector() * (cameraSpeed * deltaTime);
			m_Camera->SetPosition(m_Position);
		}

		if (Input::IsKeyPressed(KeyCode::S))
		{
			m_Position -= m_Camera->GetForwardVector() * (cameraSpeed * deltaTime);
			m_Camera->SetPosition(m_Position);
		}

		if (Input::IsKeyPressed(KeyCode::D))
		{
			m_Position += m_Camera->GetRightVector() * (cameraSpeed * deltaTime);
			m_Camera->SetPosition(m_Position);
		}

		if (Input::IsKeyPressed(KeyCode::A))
		{
			m_Position -= m_Camera->GetRightVector() * (cameraSpeed * deltaTime);
			m_Camera->SetPosition(m_Position);
		}

		auto[mouseX, mouseY] = Input::GetMousePos();

		m_Camera->AddYaw(((float)mouseX - lastMouseX) * 0.1f);
		m_Camera->AddPitch((lastMouseY - (float)mouseY) * 0.1f);
		lastMouseX = (float)mouseX;
		lastMouseY = (float)mouseY;
	}
}