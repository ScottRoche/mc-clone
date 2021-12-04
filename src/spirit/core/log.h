#pragma once

#include "spdlog/spdlog.h"

#include <memory>

namespace Spirit
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

	#define LOG_TRACE(...) Spirit::Log::GetLogger()->trace(__VA_ARGS__)
	#define LOG_DEBUG(...) Spirit::Log::GetLogger()->debug(__VA_ARGS__)
	#define LOG_INFO(...)  Spirit::Log::GetLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)  Spirit::Log::GetLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...) Spirit::Log::GetLogger()->error(__VA_ARGS__)
	#define LOG_FATAL(...) Spirit::Log::GetLogger()->critical(__VA_ARGS__)
}