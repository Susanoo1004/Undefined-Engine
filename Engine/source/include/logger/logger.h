#pragma once

#include <filesystem>
#include <fstream>
#include <format>
#include <iostream>
#include <ts_queue/tsqueue.hpp>

#define ANSI_COLOR_GRAY     "\x1b[38;5;242m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RED      "\x1b[31m"

#define ANSI_STYLE_BOLD     "\x1b[1m"

#define ANSI_RESET          "\x1b[0m"

class Logger
{
public:
	Logger();
	~Logger();

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
	static void Stop();

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

	static inline std::fstream mFile;

	static void Start();
	static void PrintEntry(LogEntry entry);

	static inline bool IsRunning = true;
	static inline std::condition_variable Sleep;

	static inline std::thread Thread = std::thread(&Logger::Start);
	static inline TsQueue<LogEntry> EntryList;
};
