#pragma once

#include "layer.h"

#include <vector>

namespace Spirit
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushObject(Layer* object);
		void PopObject(Layer* object);

		std::vector<Layer*>::iterator begin() { return m_Objects.begin(); }
		std::vector<Layer*>::iterator end() { return m_Objects.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Objects.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Objects.rend(); }

	private:
		std::vector<Layer*> m_Objects;
	};
}