#include "memory_leak.h"

#include <crtdbg.h>

#include "logger/logger.h"

void MemoryLeak::CheckMemoryLeak(bool printResult)
{
	IsMemoryLeak = printResult;
	if (printResult)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		/////// Ignore memory leaks from 167 to 171
		//_CrtSetBreakAlloc();
		
		std::cout << "STARTED MEMORY LEAK CHECK\n" << std::endl;
	}
}

void MemoryLeak::EndMemoryLeak()
{
	if (IsMemoryLeak)
	{
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
		_CrtDumpMemoryLeaks();

		std::cout << "\nENDED MEMORY LEAK CHECK" << std::endl;
	}
}
