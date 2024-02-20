#pragma once

#include <filesystem>
#include <fstream>
#include <Windows.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define DEBUG_LOG(format, ...) { \
OutputDebugStringA(__FILENAME__); \
OutputDebugStringA("("); \
OutputDebugStringA(std::to_string(__LINE__).c_str()); \
OutputDebugStringA(")"); \
OutputDebugStringA(": "); \
OutputDebugStringA(Logger::Debug.Print(format, __VA_ARGS__).c_str()); \
}


class Logger
{
private:
	std::fstream m_File;

public:
	Logger();
	~Logger();
	static Logger Debug;

	void CreateDebugFile(std::string path, std::string name);
	void CreateDebugFile(std::filesystem::path const& filename);
	void OpenFile(std::filesystem::path const& filename);
	std::string Print(const char* format, ...);
	static void Warning(const char* format, ...);
};
