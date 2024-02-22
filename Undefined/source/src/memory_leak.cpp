#include "memory_leak.h"

#include <crtdbg.h>

#include "logger/logger.h"

void MemoryLeak::CheckMemoryLeak(bool choice)
{
	IsMemoryLeak = choice;
	if (choice)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		//Logger::Error("MEMORY LEAK DETECTED AT");
	}
}

void MemoryLeak::EndMemoryLeak()
{
	if (IsMemoryLeak)
	{
		_CrtDumpMemoryLeaks();
	}
}
