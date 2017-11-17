//Portable sleep command. Depending on the OS used (detected with _WIN32), different versions will be called
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void sleepms(unsigned int ms)
{
	#ifdef _WIN32
		Sleep(ms);
	#else
		usleep(ms * 1000); //usleep takes microseconds
	#endif
}