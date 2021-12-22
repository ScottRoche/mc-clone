#pragma once

#include <spirit.h>

class ExampleLayer : public Spirit::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
private:

	std::shared_ptr<Spirit::CameraController> m_CameraController;
	std::shared_ptr<Spirit::Camera> m_Camera;

};