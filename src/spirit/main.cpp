#include <iostream>

#include <glm.hpp>

#include "core/log.h"
#include "core/window.h"

#include "renderer/renderer.h"
#include "renderer/camera.h"

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

int main(int argc, char *argv[])
{
	Spirit::Log::Init();
	LOG_INFO("Logger Initalised");

	Spirit::Window window(Spirit::WindowProps("Minecraft Clone"));
	Spirit::Camera camera(45.0f, glm::vec2(800.0f, 600.0f), 0.1f, 100.0f);
	camera.SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	camera.SetYaw(20.0f);

	Spirit::Renderer::Init();
	/* This is only temporary. There should be no GetWindowHandle and telling the
	 * window should tell the application in a callback that it has closed. */
	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		static float lastFrameTs = 0;

		float ts = glfwGetTime();
		float deltaTime = ts - lastFrameTs;
		lastFrameTs = ts;

		float s_EditVerts[sizeof(s_SampleVerts)/sizeof(float)];
		memcpy(s_EditVerts, s_SampleVerts, sizeof(s_SampleVerts));

		window.OnUpdate();

		camera.SetYaw(200.0f * deltaTime);


		Spirit::Renderer::BeginScene(camera);

		Spirit::Renderer::Submit(s_SampleVerts, sizeof(s_SampleVerts));
	
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < sizeof(s_EditVerts) / sizeof(float); j += 6)
			{
				s_EditVerts[j] -= 2.0f;
			}
			Spirit::Renderer::Submit(s_EditVerts, sizeof(s_EditVerts));
		}
		Spirit::Renderer::EndScene();
	}

	Spirit::Renderer::Deinit();
	return 0;
}