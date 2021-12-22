#pragma once

#include "engine/sprtpch.h"

#include "core/key_codes.h"
#include "core/input.h"

#include "camera.h"

namespace Spirit
{
	class CameraController
	{
	public:
		CameraController(std::shared_ptr<Camera> camera);
		~CameraController();
		void OnUpdate(float deltaTime);

	private:
		std::shared_ptr<Camera> m_Camera;
		glm::vec3 m_Position;
	};
}