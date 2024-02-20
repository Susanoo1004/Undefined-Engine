#include "logger/logger.h"
#include <stdarg.h>
#include <iostream>

Logger Logger::Debug;

std::string currentDateTime() {
    std::time_t t = std::time(nullptr);

    std::tm now;
    localtime_s(std::addressof(now), std::addressof(t));

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y.%m.%d-%H.%M.%S", &now);
    return buffer;
}

Logger::Logger()
{
    Logger::Debug.CreateDebugFile(std::string("../log/"), currentDateTime());
}
Logger::~Logger()
{
    m_File.close();
}

void Logger::CreateDebugFile(std::string path, std::string name)
{
    std::filesystem::path const& filename = path + name + ".txt";
    int fileCount = 0;

    for (auto& p : std::filesystem::directory_iterator(path))
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

void Logger::CreateDebugFile(std::filesystem::path const& filename)
{
    std::filesystem::path path = filename.parent_path();

    int fileCount = 0;

    for (auto& p : std::filesystem::directory_iterator(path))
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


void Logger::OpenFile(std::filesystem::path const& filename)
{
    m_File.open(filename);
    if (m_File.is_open())
    {
        m_File.clear();
        std::cout << "File " << filename << " found" << std::endl;
    }
    else
    {
        std::cout << "File " << filename << " does not exist" << std::endl;
    }
}

std::string Logger::Print(const char* format, ...)
{
    char buffer[1024];
    va_list list;
    va_start(list, format);

    if (!m_File.is_open())
        CreateDebugFile(std::string("assets/Debug/"), currentDateTime());

    vsprintf_s(buffer, sizeof(buffer), format, list);
    format = buffer;

    va_end(list);
    std::cout << format;
    if (m_File.is_open())
    {
        m_File << format;
        m_File.flush();
    }
    return format;
}

void Logger::Warning(const char* format, ...)
{
    char buffer[1024];
    va_list list;
}
