#include "Sleep.h"

void sleepms(unsigned int ms)
{
	#ifdef _WIN32
		Sleep(ms);
	#else
		usleep(ms * 1000); //usleep takes microseconds
	#endif
}
