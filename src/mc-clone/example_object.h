#include <spirit.h>

#include <memory>

class ExampleObject : public Spirit::Object
{
public:
	ExampleObject();

	virtual void OnBegin() override { LOG_INFO("Example Object Begin"); }
	virtual void OnEnd() override { LOG_INFO("Example Object End"); }
	virtual void OnUpdate(float deltaTime) override;

protected:
	std::string m_Name;
	std::unique_ptr<Spirit::Camera> m_Camera;
};