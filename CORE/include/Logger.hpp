// CORE/include/Logger.hpp

#pragma once
#include "Export.hpp"

#include <string>
#include <vector>

namespace Lobster
{
	enum LOBSTER_API LogLevel : unsigned char
	{
		LOG_LEVEL_UNKNOWN = 255,
		LOG_LEVEL_DEBUG = 0,
		LOG_LEVEL_INFO = 1,
		LOG_LEVEL_WARNING = 2,
		LOG_LEVEL_ERROR = 3,
	};

	class LOBSTER_API Logger
	{
	public:
		static void Info(const std::string& message) { Log(LOG_LEVEL_INFO,message); }
		static void Debug(const std::string& message) { Log(LOG_LEVEL_DEBUG,message); }
		static void Warning(const std::string& message) { Log(LOG_LEVEL_WARNING,message); }
		static void Error(const std::string& message) { Log(LOG_LEVEL_ERROR,message); }

		static void Info(std::vector<std::string> messages) { Log(LOG_LEVEL_INFO,messages); }
		static void Debug(std::vector<std::string> messages) { Log(LOG_LEVEL_DEBUG,messages); }
		static void Warning(std::vector<std::string> messages) { Log(LOG_LEVEL_WARNING,messages); }
		static void Error(std::vector<std::string> messages) { Log(LOG_LEVEL_ERROR,messages); }

		static void DrawImguiConsole();
	private:
		struct LOBSTER_API LogEntry
		{
			LogLevel level = LOG_LEVEL_UNKNOWN;
			std::string message = "";
		};

		static std::vector<LogEntry> logs;
		static bool autoscroll;
		static const unsigned int max_logs = 2000;

		static inline std::string LevelToString(LogLevel level)
		{
			switch(level)
			{
			case LOG_LEVEL_DEBUG:
				return " [DEBUG] ";
			case LOG_LEVEL_INFO:
				return " [INFO] ";
			case LOG_LEVEL_WARNING:
				return " [WARNING] ";
			case LOG_LEVEL_ERROR:
				return " [ERROR] ";
			default:
				return " [UNKNOWN] ";
			}
		}
	private:
		static void Log(LogLevel lvl,const std::string& message);
		static void Log(LogLevel lvl,std::vector<std::string> messages);
	};
}