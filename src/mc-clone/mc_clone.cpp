#include <spirit.h>
#include "core/entry_point.h"

#include "example_object.h"

class MCClone : public Spirit::Application
{
public:
	MCClone()
	{
		LOG_WARN("MC_CLONE Started");
		m_ObjectStack.PushObject(new ExampleObject());
	}

	~MCClone() override
	{
		LOG_WARN("MC_CLONE Closed");
	}
};

Spirit::Application* Spirit::CreateApplication()
{
	return new MCClone();
}