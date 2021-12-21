#pragma once

#include "engine/sprtpch.h"

namespace Spirit
{
	/* The lowest level class for an object within the engine */
	class Object
	{
	public:
		Object(const std::string& name = "Default Object");
		virtual ~Object() = default;

		virtual void OnBegin() {}
		virtual void OnEnd() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent() {}
		virtual const std::string& ToString() {}

		const std::string& GetName() { return m_Name; }

	protected:
		std::string m_Name;
	};
}