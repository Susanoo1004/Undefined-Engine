#pragma once

#include <filesystem>
#include <fstream>
#include <format>
#include <iostream>
#include <ts_queue/tsqueue.hpp>
#include <toolbox/Vector3.h>

#include "utils/flag.h"

template <>
struct std::formatter<Vector3, char> 
{
	template<class ParseContext>
	constexpr ParseContext::iterator parse(ParseContext& ctx)
	{
		auto it = ctx.begin();
		if (it == ctx.end())
			return it;
		if (*it != '}')
			throw std::format_error("Invalid format args for Vector3");
		return it;
	}

	template<class FmtContext>
	typename FmtContext::iterator format(const Vector3& vec, FmtContext& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
	}
};

class Logger
{
public:
	UNDEFINED_ENGINE Logger();
	UNDEFINED_ENGINE ~Logger();

private:
	enum class LogLevel
	{
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR,
		FATALERROR,
	};

	struct LogEntry
	{
		LogLevel Level;
		std::string Log;
		std::chrono::system_clock::time_point TimeOffset;
	};

public:
	UNDEFINED_ENGINE static void Stop();

	template<class... Types>
	static void Debug(std::string string, Types... args)
	{	
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::DEBUG, log);
	}

	template<class... Types>
	static void Info(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::INFO, log);
	}

	template<class... Types>
	static void Warning(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::WARNING, log);
	}

	template<class... Types>
	static void Error(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::ERROR, log);
	}

	template<class... Types>
	static void FatalError(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::FATALERROR, log);
	}

private:
	static std::string CurrentDateTime();
	static void CreateDebugFile(std::string path, std::string name);
	static void SetupLogEntry(LogLevel level, std::string log);

	UNDEFINED_ENGINE static inline std::fstream mFile;

	static void Start();
	static void PrintEntry(LogEntry entry);

	UNDEFINED_ENGINE static inline bool IsRunning = true;
	UNDEFINED_ENGINE static inline std::condition_variable Sleep;

	UNDEFINED_ENGINE static inline std::thread Thread = std::thread(&Logger::Start);
	UNDEFINED_ENGINE static inline TsQueue<LogEntry> EntryList;
};
