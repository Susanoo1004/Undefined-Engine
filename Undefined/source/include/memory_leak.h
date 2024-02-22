#pragma once

#include "utils/flag.h"

class MemoryLeak
{
public:
	static void CheckMemoryLeak(bool choice = false);
	static void EndMemoryLeak();

private:
	static inline bool IsMemoryLeak;
};