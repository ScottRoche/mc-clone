#pragma once

#include <cstdint>

namespace Spirit
{
	class Renderer
	{
	public:
		static void Init();
		static void Deinit();

		static void Submit(float* meshData, uint32_t dataSize);
		static void Draw();
	};
}