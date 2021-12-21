#pragma once

#include "application.h"

extern Spirit::Application* Spirit::CreateApplication();

int main(int argc, char* argv[])
{
	auto app = Spirit::CreateApplication();
	app->Run();
	delete app;
	return 0;
}