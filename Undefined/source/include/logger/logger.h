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
private:
	static inline std::fstream m_File;

	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error,
		FatalError,
	};

	struct LogEntry
	{
		LogLevel Level;
		std::string Log;
		std::chrono::system_clock::time_point TimeOffset;
	};

	static void Start();
	static void PrintEntry(LogEntry entry);

	static inline bool isRunning = true;
	static inline std::condition_variable sleep;

	static inline TsQueue<LogEntry> EntryList;
	static inline std::thread thread = std::thread(&Logger::Start);

public:
	Logger();
	~Logger();
	
	static void Stop();

	static void CreateDebugFile(std::string path, std::string name);
	static void SetupLogEntry(LogLevel level, std::string log);

	template<class... Types>
	static void Debug(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::Debug, log);
	}

	template<class... Types>
	static void Log(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::Info, log);
	}

	template<class... Types>
	static void Warning(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::Warning, log);
	}

	template<class... Types>
	static void Error(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));

		SetupLogEntry(LogLevel::Error, log);
	}

	template<class... Types>
	static void FatalError(std::string string, Types... args)
	{
		std::string log = std::vformat(string, std::make_format_args(args...));
		
		SetupLogEntry(LogLevel::FatalError, log);
	}
};
