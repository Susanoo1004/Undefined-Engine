#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif