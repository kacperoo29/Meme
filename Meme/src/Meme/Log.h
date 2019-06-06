#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Meme {

	class MEME_API Log
	{
	public:		
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define MEME_CORE_TRACE(...)	::Meme::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MEME_CORE_INFO(...)		::Meme::Log::getCoreLogger()->info(__VA_ARGS__)
#define MEME_CORE_WARN(...)		::Meme::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MEME_CORE_ERROR(...)	::Meme::Log::getCoreLogger()->error(__VA_ARGS__)
#define MEME_CORE_FATAL(...)	::Meme::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define MEME_TRACE(...)	::Meme::Log::getClientLogger()->trace(__VA_ARGS__)
#define MEME_INFO(...)	::Meme::Log::getClientLogger()->info(__VA_ARGS__)
#define MEME_WARN(...)	::Meme::Log::getClientLogger()->warn(__VA_ARGS__)
#define MEME_ERROR(...)	::Meme::Log::getClientLogger()->error(__VA_ARGS__)
#define MEME_FATAL(...)	::Meme::Log::getClientLogger()->fatal(__VA_ARGS__)


