#pragma once

#include <glm.hpp>

namespace Spirit
{
	class Camera
	{
	public:
		Camera() = default;

		Camera(float fieldOfView,
		       const glm::vec2& viewportDimensions,
		       float nearPlane,
		       float farPlane);

		glm::mat4 GetProjection() const { return m_Projection; }
		glm::mat4 GetViewMatrix() const;

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetForwardVector() { return m_ForwardVector; }
		const glm::vec3& GetUpVector() { return m_UpVector; }
		const glm::vec3& GetRightVector() { return m_RightVector; }

		void SetPosition(const glm::vec3& transform);
		void AddPitch(float degree);
		void AddYaw(float degree);

	private:
		void CreatePerspectiveProjection();
		void UpdateVectors();

	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);

		glm::vec2 m_ViewportDimensions;
		float m_FieldOfView;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation;

		glm::vec3 m_ForwardVector;
		glm::vec3 m_RightVector;
		glm::vec3 m_UpVector;
	};
}