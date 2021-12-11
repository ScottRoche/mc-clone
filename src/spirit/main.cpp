#include <iostream>

#include "core/log.h"
#include "core/window.h"

#include "renderer/renderer.h"

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

	Spirit::Renderer::Init();
	/* This is only temporary. There should be no GetWindowHandle and telling the
	 * window should tell the application in a callback that it has closed. */
	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		Spirit::Renderer::Submit(s_SampleVerts, sizeof(s_SampleVerts));

		window.OnUpdate();
		Spirit::Renderer::Draw();
	}

	Spirit::Renderer::Deinit();
	return 0;
}