#pragma once

#include <cstdint>

#include "camera.h"

namespace Spirit
{
	class Renderer
	{
	public:
		static void Init(const Camera& camera);
		static void Deinit();

		static void Submit(float* meshData, uint32_t dataSize);
		static void Draw();
	};
}