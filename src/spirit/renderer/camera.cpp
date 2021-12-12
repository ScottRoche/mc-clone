#include "camera.h"

#include <gtc/matrix_transform.hpp>

namespace Spirit
{
	Camera::Camera(float fieldOfView,
	               const glm::vec2& viewportDimensions,
	               float nearPlane,
	               float farPlane)
		: m_FieldOfView(fieldOfView), m_ViewportDimensions(viewportDimensions)
	{
		m_Projection = glm::perspective(glm::radians(m_FieldOfView),
		                                m_ViewportDimensions[0] / m_ViewportDimensions[1],
		                                nearPlane,
		                                farPlane);
	}

	void Camera::SetPerspective(float nearPlane, float farPlane)
	{
		m_Projection = glm::perspective(glm::radians(m_FieldOfView),
		                                m_ViewportDimensions[0] / m_ViewportDimensions[1],
		                                nearPlane,
		                                farPlane);
	}

	void Camera::SetPosition(const glm::vec3& transform)
	{
		m_View = glm::translate(m_View, transform);
	}

	void Camera::SetPitch(float degree)
	{
		m_View = glm::rotate(m_View, glm::radians(degree), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void Camera::SetYaw(float degree)
	{
		m_View = glm::rotate(m_View, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}