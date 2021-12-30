#pragma once

#include "engine/sprtpch.h"

#include "event.h"

namespace Spirit
{
	/* The lowest level class for an object within the engine */
	class Layer
	{
	public:
		Layer(const std::string& name = "Default Object");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(Event& event) {}

		virtual const std::string& ToString() {}

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}