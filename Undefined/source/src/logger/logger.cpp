#include "logger/logger.h"

#include <stdarg.h>
#include <mutex>
#include <Windows.h>

std::string currentDateTime() {
    std::time_t t = std::time(nullptr);

    std::tm now;
    localtime_s(std::addressof(now), std::addressof(t));

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H-%M-%S", &now);
    return buffer;
}

Logger::Logger()
{
    CreateDebugFile(std::string("../log/"), currentDateTime());
}
Logger::~Logger()
{
    m_File.close();
}

void Logger::CreateDebugFile(std::string path, std::string name)
{
    std::filesystem::path const& filename = path + name + ".txt";
    int fileCount = 0;

    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);

        std::cout << "Directory " << path << " created" << std::endl;
    }

    
    for ([[maybe_unused]]auto& p : std::filesystem::directory_iterator(path))
        ++fileCount;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (fileCount >= 4)
        {
            remove(entry);
            break;
        }
    }

    m_File.open(filename, std::fstream::out);
    if (m_File.is_open())
        std::cout << "File " << filename << " created" << std::endl;
    else
        std::cout << "File " << filename << " could not be created" << std::endl;
}

void Logger::SetupLogEntry(LogLevel level, std::string log)
{
    LogEntry entry;
    entry.Level = level;
    entry.Log = log;
    EntryList.Push(entry);
    sleep.notify_one();
}

void Logger::Start()
{
    std::mutex mutex;
    (void)SetThreadDescription(thread.native_handle(), L"Logger Thread");

    std::unique_lock lock(mutex);
    while (isRunning)
    {
        sleep.wait(lock, [] {return (!EntryList.Empty() || !isRunning); });

        while (!EntryList.Empty())
        {
            PrintEntry(EntryList.Pop());
        }

        std::cout.flush();
    }
}

void Logger::PrintEntry(LogEntry entry)
{
    std::string log = entry.Log + '\n';
    const char* color = ANSI_RESET;

    switch (entry.Level)
    {
    case LogLevel::Debug:
        color = ANSI_COLOR_GRAY;
        log = "[DEBUG] " + log;
        break;

    case LogLevel::Info:
        color = ANSI_RESET;
        log = "[INFO] " + log;
        break;

    case LogLevel::Warning:

        color = ANSI_COLOR_YELLOW;
        log = "[WARNING] " + log;
        break;

    case LogLevel::Error:

        color = ANSI_COLOR_RED;
        log = "[ERROR] " + log;
        break;

    case LogLevel::FatalError:
        color = ANSI_COLOR_RED ANSI_STYLE_BOLD;
        log = "[FATAL ERROR] " + log;
        break;
    }

    std::cout << color << log << ANSI_RESET;
    
    if (m_File.is_open())
    {
        m_File << log;
    }
}

void Logger::Stop()
{
    isRunning = false;
    sleep.notify_one();

    if (thread.joinable())
    {
        thread.join();
    }
}