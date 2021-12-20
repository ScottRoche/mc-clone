#pragma once

#include "event.h"
#include "core/mouse_codes.h"

namespace Spirit
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y)
			: m_XPos(x), m_YPos(y) {}

		double GetX() const { return m_XPos; }
		double GetY() const { return m_YPos; }

		EVENT_TYPE(MouseMoved);
	private:
		double m_XPos;
		double m_YPos;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button)
			: m_Button((MouseButton)button) {}

		MouseButton GetButton() const { return m_Button; }

		EVENT_TYPE(MouseButtonPressed);
	private:
		MouseButton m_Button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int button)
			: m_Button((MouseButton)button) {}

		MouseButton GetButton() const { return m_Button; }

		EVENT_TYPE(MouseButtonReleased);
	private:
		MouseButton m_Button;
	};
}