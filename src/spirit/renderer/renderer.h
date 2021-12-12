#pragma once

#include <cstdint>

#include "camera.h"

namespace Spirit
{
	class Renderer
	{
	public:
		static void Init();
		static void Deinit();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(float* meshData, uint32_t dataSize);

		static void SetViewportSize(uint32_t width, uint32_t height);

	private:
		static void Flush();
		static void Draw();

	};
}