#ifdef UNDEFINED_EXPORT
#define UNDEFINED_ENGINE __declspec(dllexport)
#else #ifdef UNDEFINED_EXPORT
#define UNDEFINED_ENGINE __declspec(dllimport)
#endif

//#ifdef _DEBUG
//	#define _CRTDBG_MAP_ALLOC
//	#include <stdlib.h>
//	#include <crtdbg.h>
//	#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
//	#define new DEBUG_NEW
//#endif

#define ANSI_COLOR_GRAY     "\x1b[38;5;242m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RED      "\x1b[31m"

#define ANSI_STYLE_BOLD     "\x1b[1m"

#define ANSI_RESET          "\x1b[0m"