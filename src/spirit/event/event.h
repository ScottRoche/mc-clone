#pragma once

#include <string>

namespace Spirit
{
	enum class EventType
	{
		NONE = 0,
		WindowClose, WindowResize,
		KeyPressed, KeyReleased,
		MouseMoved, MouseButtonPressed, MouseButtonReleased
	};

	#define EVENT_TYPE(_type) static EventType GetStaticType() { return EventType::_type; } \
	                          virtual EventType GetType() const override { return GetStaticType(); }                  \
	                          virtual std::string GetName() const override { return #_type; }

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual std::string GetName() const = 0;
		virtual EventType GetType() const = 0;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T, typename F>
		void Dispatch(const F& func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				func(static_cast<T&>(m_Event));
			}
		}

	private:
		Event& m_Event;
	};
}