#include <spirit.h>
#include "core/entry_point.h"

class MCClone : public Spirit::Application
{
public:
	MCClone()
	{
		LOG_WARN("MC_CLONE Started");
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