#include <iostream>

#include "log.h"

int main(int argc, char *argv[])
{
	Spirit::Log::Init();
	LOG_INFO("Logger Initalised");

	return 0;
}