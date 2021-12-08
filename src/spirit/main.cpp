#include <iostream>

#include "core/log.h"
#include "core/window.h"

#include "renderer/renderer.h"

int main(int argc, char *argv[])
{
	Spirit::Log::Init();
	LOG_INFO("Logger Initalised");

	Spirit::Window window(Spirit::WindowProps("Minecraft Clone"));

	Spirit::RendererInit();
	/* This is only temporary. There should be no GetWindowHandle and telling the
	 * window should tell the application in a callback that it has closed. */
	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		Spirit::Draw();
		window.OnUpdate();
	}

	Spirit::RendererDeinit();
	return 0;
}