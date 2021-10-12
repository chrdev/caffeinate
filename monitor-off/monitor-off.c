// MonitorOff v1.0.0
// Turn down the display 1immediately
//
// By chrdev, 2021
// BSD Zero Clause License
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")


#define MONITOR_OFF 2


int wmain(void) {
	// If run by a mouse click, a little mouse movements may follow.
	// Sleep() eliminate this interference.
	Sleep(GetDoubleClickTime());
	int ret = SendMessageW(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, MONITOR_OFF);
	ExitProcess(ret);
}
