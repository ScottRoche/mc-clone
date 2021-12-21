#include "object_stack.h"

namespace Spirit
{
	ObjectStack::~ObjectStack()
	{
		for (auto object : m_Objects)
		{
			object->OnEnd();
			delete object;
		}
	}

	void ObjectStack::PushObject(Object* object)
	{
		m_Objects.emplace_back(object);
		object->OnBegin();
	}

	void ObjectStack::PopObject(Object* object)
	{
		auto itr = std::find(m_Objects.begin(), m_Objects.end(), object);
		if (itr != m_Objects.end())
		{
			object->OnEnd();
			m_Objects.erase(itr);
		}
	}
}