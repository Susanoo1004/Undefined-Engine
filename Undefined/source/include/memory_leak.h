#pragma once

#include "utils/flag.h"

class MemoryLeak
{
public:
	static void CheckMemoryLeak(bool printResult = false);
	static void EndMemoryLeak();

private:
	static inline bool IsMemoryLeak;
};