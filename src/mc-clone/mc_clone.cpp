#include <spirit.h>
#include "core/entry_point.h"

#include "example_layer.h"

class MCClone : public Spirit::Application
{
public:
	MCClone()
	{
		LOG_WARN("MC_CLONE Started");
		layer = new ExampleLayer();
		m_LayerStack.PushObject(layer);
	}

	~MCClone() override
	{
		m_LayerStack.PopObject(layer);
		delete layer;
		LOG_WARN("MC_CLONE Closed");
	}

ExampleLayer* layer;

};

Spirit::Application* Spirit::CreateApplication()
{
	return new MCClone();
}