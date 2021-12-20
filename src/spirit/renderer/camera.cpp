#include "camera.h"

#include <gtc/matrix_transform.hpp>

#include "core/log.h"

namespace Spirit
{
	Camera::Camera(float fieldOfView,
	               const glm::vec2& viewportDimensions,
	               float nearPlane,
	               float farPlane)
		: m_FieldOfView(fieldOfView), m_ViewportDimensions(viewportDimensions)
	{
		CreatePerspectiveProjection();

		m_ForwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
		m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, m_UpVector));
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		AddPitch(0.0f);
		AddYaw(0.0f);
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		LOG_DEBUG("Position: {:f}, {:f}, {:f} Rotation: {:f}, {:f}, {:f}",
		          m_Position.x, m_Position.y, m_Position.z,
		          m_Rotation.x, m_Rotation.y, m_Rotation.z);
		return glm::lookAt(m_Position, m_Position + m_ForwardVector, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void Camera::AddPitch(float degree)
	{
		glm::vec3 direction = glm::vec3(0.0f);
		
		m_Rotation.y += degree;
		if (m_Rotation.y > 89.0f)
		{
			m_Rotation.y = 89.0f;
		}
		else if (m_Rotation.y < -89.0f)
		{
			m_Rotation.y = -89.0f;
		}
		UpdateVectors();
	}

	void Camera::AddYaw(float degree)
	{
		m_Rotation.x += degree;
		UpdateVectors();
	}

	void Camera::CreatePerspectiveProjection()
	{
		m_Projection = glm::perspective(m_FieldOfView,
		                                m_ViewportDimensions.x / m_ViewportDimensions.y,
		                                0.1f, 100.0f);
	}

	void Camera::UpdateVectors()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Rotation.x)) * cos(glm::radians(m_Rotation.y));
		direction.y = sin(glm::radians(m_Rotation.y));
		direction.z = sin(glm::radians(m_Rotation.x)) * cos(glm::radians(m_Rotation.y));

		m_ForwardVector = glm::normalize(direction);
		m_RightVector = glm::normalize(glm::cross(m_ForwardVector, m_UpVector));
	}
}