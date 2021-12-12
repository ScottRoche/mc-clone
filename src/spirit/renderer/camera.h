#pragma once

#include <glm.hpp>

namespace Spirit
{
	class Camera
	{
	public:
		Camera() = default;

		Camera(glm::mat4& projection)
			: m_Projection(projection) {}

		Camera(float fieldOfView,
		       const glm::vec2& viewportDimensions,
		       float nearPlane,
		       float farPlane);

		void SetPerspective(float nearPlane, float farPlane);
		glm::mat4 GetProjection() const { return m_Projection; }

		void SetPosition(const glm::vec3& transform);
		void SetPitch(float degree);
		void SetYaw(float degree);

		glm::mat4 GetView() const { return m_View; }

	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);

		glm::vec2 m_ViewportDimensions;
		float m_FieldOfView = 45.0f;
	};
}