#pragma once

#include <spirit.h>

#include "renderer/texture.h"

class ExampleLayer : public Spirit::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Spirit::Event& event) override;

private:
	void SetDrawMode(Spirit::KeyPressedEvent& event);

private:

	std::shared_ptr<Spirit::CameraController> m_CameraController;
	std::shared_ptr<Spirit::Camera> m_Camera;

	std::shared_ptr<Spirit::Texture> m_BottomTexture;
	std::shared_ptr<Spirit::Texture> m_SidesTexture;
	std::shared_ptr<Spirit::Texture> m_TopTexture;
};