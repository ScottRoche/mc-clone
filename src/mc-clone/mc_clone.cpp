#include <spirit.h>
#include "core/entry_point.h"

#include "example_layer.h"

class MCClone : public Spirit::Application
{
public:
	MCClone()
	{
		LOG_WARN("MC_CLONE Started");
		obj = new ExampleLayer();
		m_ObjectStack.PushObject(obj);
	}

	~MCClone() override
	{
		m_ObjectStack.PopObject(obj);
		delete obj;
		LOG_WARN("MC_CLONE Closed");
	}

ExampleLayer* obj;

};

Spirit::Application* Spirit::CreateApplication()
{
	return new MCClone();
}