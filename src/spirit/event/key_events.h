#pragma once

#include "event.h"
#include "core/key_codes.h"

namespace Spirit
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int key)
			: m_KeyCode((KeyCode)key) {}

		KeyCode GetKey() const { return m_KeyCode; }

		EVENT_TYPE(KeyPressed);
	private:
		KeyCode m_KeyCode;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int key)
			: m_KeyCode((KeyCode)key) {}

		KeyCode GetKey() const { return m_KeyCode; }

		EVENT_TYPE(KeyReleased);
	private:
		KeyCode m_KeyCode;
	};
}