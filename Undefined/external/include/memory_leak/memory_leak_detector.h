#pragma once

#include <crtdbg.h>

class MemoryLeakDetector
{
public:
    MemoryLeakDetector();

    ~MemoryLeakDetector();

    MemoryLeakDetector(const MemoryLeakDetector& other) = delete;
    
    MemoryLeakDetector(MemoryLeakDetector&& other) = delete;
    
    MemoryLeakDetector& operator=(const MemoryLeakDetector& other) = delete;
    
    MemoryLeakDetector& operator=(MemoryLeakDetector&& other) = delete;

private:
    static void ReportFailure(size_t unfreedBytes);

    _CrtMemState m_MemState;
};