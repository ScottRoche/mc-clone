#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Spirit
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^%n: %v%$");

		s_Logger = spdlog::stdout_color_mt("Log");
		s_Logger->set_level(spdlog::level::trace);
	}
}