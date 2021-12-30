#include "example_layer.h"

#include <memory>
#include <array>

#include "core/base.h"

static float s_SampleVerts[] = {
	// Front
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
	0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
	0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-right

	// Back
	-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-left
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-right

	// Left
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-top
	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-front
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-back
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right

	// Right
	0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // front-top
	0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-front
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom-back
	0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right

	// Top
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // front-top
	0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-front
	0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-back
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-right

	// Bottom
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // front-top
	0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // bottom-front
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-back
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // top-right
};

void ExampleLayer::OnAttach()
{
	m_Camera = std::make_shared<Spirit::Camera>(45.0f, glm::vec2(800, 600), 0.1f, 100.0f);
	m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_CameraController = std::make_shared<Spirit::CameraController>(m_Camera);
}

void ExampleLayer::OnDetach()
{

}

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

void ExampleLayer::OnUpdate(float deltaTime)
{
	m_CameraController->OnUpdate(deltaTime);

	Spirit::Renderer::BeginScene(*m_Camera);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int z = 0; z < 3; z++)
			{
				float mesh[144];
				memcpy(mesh, s_SampleVerts, sizeof(s_SampleVerts));
				for (int k = 0; k < ARRAY_SIZE(mesh); k += 6)
				{
					mesh[k + 0] += i;
					mesh[k + 1] -= z;
					mesh[k + 2] -= j;
				}
				Spirit::Renderer::Submit(mesh, sizeof(mesh));
			}
		}
	}

	Spirit::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Spirit::Event& event)
{
	Spirit::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<Spirit::KeyPressedEvent>(SPRT_BIND_FN(ExampleLayer::SetDrawMode));
}

void ExampleLayer::SetDrawMode(Spirit::KeyPressedEvent& event)
{
	static bool wireframeMode = false;

	if (event.GetKey() == Spirit::KeyCode::Esc)
	{
		wireframeMode = !wireframeMode;
	}

	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
