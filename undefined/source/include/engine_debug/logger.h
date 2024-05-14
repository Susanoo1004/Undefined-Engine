#pragma once

#include <filesystem>
#include <fstream>
#include <format>
#include <iostream>
#include <ts_queue/tsqueue.hpp>
#include <toolbox/Vector3.h>

#include "utils/flag.h"

/// <summary>
/// A Class for a Logger to debug
/// </summary>
class Logger
{
public:
	UNDEFINED_ENGINE Logger();
	UNDEFINED_ENGINE ~Logger();

private:
	/// <summary>
	/// Enum where we put different level of warning/error
	/// </summary>
	enum class LogLevel
	{
		DEBUG = 0,
		INFO,
		WARNING,
		ERROR,
		FATALERROR,
	};

	/// <summary>
	/// Struct used to set the level, the string log and the time offset of the Entry
	/// </summary>
	struct LogEntry
	{
		LogLevel Level;
		std::string Log;
		std::chrono::system_clock::time_point TimeOffset;
	};

public:
	/// <summary>
	/// Stop the Logger thread
	/// </summary>
	UNDEFINED_ENGINE static void Stop();
	UNDEFINED_ENGINE static void CheckForExit();

	template<class... Types>
	static void Debug(std::string string, Types... args)
	{	
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::DEBUG, log);
	}

	template<class... Types>
	static void Info(std::string entryString, Types... args)
	{
		std::string log = std::vformat(entryString, std::make_format_args(args...));

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
	static void CreateDebugFile(const std::string& path, const std::string& mName);
	static void SetupLogEntry(LogLevel level, const std::string& log);

	UNDEFINED_ENGINE static inline std::fstream mFile;

	static void Start();
	static void PrintEntry(LogEntry entry);

	UNDEFINED_ENGINE static inline bool IsRunning = true;
	UNDEFINED_ENGINE static inline std::condition_variable Sleep;

	UNDEFINED_ENGINE static inline std::thread Thread = std::thread(&Logger::Start);
	UNDEFINED_ENGINE static inline TsQueue<LogEntry> EntryList;
};
