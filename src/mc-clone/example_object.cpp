#include "example_object.h"

#include <glm.hpp>

static float s_ExampleObject[] = {
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

ExampleObject::ExampleObject()
	: m_Name("Example Object")
{
	m_Camera = std::make_unique<Spirit::Camera>(45.0f, glm::vec2(800, 600), 0.1f, 100.0f);
	m_Camera->SetPosition(glm::vec3(-20.0f, 0.0f, 0.0f));
}

void ExampleObject::OnUpdate(float deltaTime)
{
	Spirit::Renderer::BeginScene(*m_Camera);
	Spirit::Renderer::Submit(s_ExampleObject, sizeof(s_ExampleObject));
	Spirit::Renderer::EndScene();
}