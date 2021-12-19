#pragma once

#include <tuple>

#include "key_events.h"
#include "mouse_events.h"

namespace Spirit
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsButtonPressed(MouseButton button);
		static std::tuple<float, float> GetMousePos();
	};
}