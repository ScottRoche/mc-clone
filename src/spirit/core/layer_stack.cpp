#include "layer_stack.h"

namespace Spirit
{
	LayerStack::~LayerStack()
	{
		for (auto object : m_Objects)
		{
			object->OnDetach();
			delete object;
		}
	}

	void LayerStack::PushObject(Layer* object)
	{
		m_Objects.emplace_back(object);
		object->OnAttach();
	}

	void LayerStack::PopObject(Layer* object)
	{
		auto itr = std::find(m_Objects.begin(), m_Objects.end(), object);
		if (itr != m_Objects.end())
		{
			object->OnDetach();
			m_Objects.erase(itr);
		}
	}
}