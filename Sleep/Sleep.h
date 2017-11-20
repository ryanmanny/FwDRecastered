#pragma once

//Portable sleep command. Depending on the OS used (detected with _WIN32), different versions will be called
void sleepms(unsigned int ms);

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
