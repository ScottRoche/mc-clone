#pragma once

#include "object.h"

#include <vector>

namespace Spirit
{
	class ObjectStack
	{
	public:
		ObjectStack() = default;
		~ObjectStack();

		void PushObject(Object* object);
		void PopObject(Object* object);

		std::vector<Object*>::iterator begin() { return m_Objects.begin(); }
		std::vector<Object*>::iterator end() { return m_Objects.end(); }
		std::vector<Object*>::reverse_iterator rbegin() { return m_Objects.rbegin(); }
		std::vector<Object*>::reverse_iterator rend() { return m_Objects.rend(); }

	private:
		std::vector<Object*> m_Objects;
	};
}