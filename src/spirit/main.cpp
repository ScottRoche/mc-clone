#include <iostream>

#include "core/log.h"
#include "core/window.h"

int main(int argc, char *argv[])
{
	Spirit::Log::Init();
	LOG_INFO("Logger Initalised");

	Spirit::Window window(Spirit::WindowProps("Minecraft Clone"));

	/* This is only temporary. There should be no GetWindowHandle and telling the
	 * window should tell the application in a callback that it has closed. */
	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.OnUpdate();
	}

	return 0;
}