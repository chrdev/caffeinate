// Caffeinate v1.0.1
// Keeps the system awake.
//
// Author: chrdev, 2023
// License: BSD Zero Clause
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h> // CommandLineToArgvW

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")

#include <stdbool.h>

int wprintf_s(const wchar_t* const format, ...);


enum {
	kMonitorOffDelay = 7, // In seconds.
};

typedef struct Command{
	unsigned help : 1;
	unsigned leaveMonitorOn : 1;
}Command;

typedef enum Status {
	status_kBegin,
	status_kNormal = status_kBegin,
	status_kNonSleep,
	status_kWaitingToQuit,
	status_kEnd
}Status;


static inline Command
parseArgs(int argc, wchar_t** argv) {
	Command cmd = { 0 };

	for(int i = 1; i < argc; ++i) {
		for(int j = 0; argv[i][j]; ++j) {
			switch(argv[i][j]) {
			case L'/':
			case L'-':
				break;
			case L'd':
			case L'D':
			case L'm':
			case L'M':
				cmd.leaveMonitorOn = true;
				argv[i][j + 1] = L'\0';
				break;
			default:
				cmd.help = true;
				argv[i][j + 1] = L'\0';
				break;
			}
		}
	}
	return cmd;
}

static inline Command
getCommand(void) {
	Command cmd = {
		.help = 1,
	};

	int argc;
	wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (!argv) return cmd;
	cmd = parseArgs(argc, argv);
	LocalFree(argv);
	return cmd;
}

static inline void
printHelp(void) {
	static const wchar_t text[] = 
		L"Caffeinate v1.0.1 | chrdev | BSD Zero Clause\n"
		L"Keeps the system awake.\n"
		L"  /D, /M  Don\'t turn off monitor\n"
		L"  /?      Show help (this message)\n";
	wprintf_s(text);
}

static void
printStatus(Status status) {
	static const wchar_t* text[] = {
		[status_kNormal        - status_kBegin] = L"End non-sleep mode.\n",
		[status_kNonSleep      - status_kBegin] = L"In non-sleep mode...\n",
		[status_kWaitingToQuit - status_kBegin] = L"Press any key to quit...\n",
	};

	wprintf_s(text[status - status_kBegin]);
}

static inline bool
isKeyUp(HANDLE stdIn) {
	static bool wasDown = false;
	INPUT_RECORD ir;
	DWORD eventCount;
	if (!ReadConsoleInputW(stdIn, &ir, 1, &eventCount)) return false;
	if (ir.EventType != KEY_EVENT) return false;
	if (ir.Event.KeyEvent.bKeyDown) {
		wasDown = true;
		return false;
	}
	if (!wasDown) return false;
	return true;
}

static inline void
waitForStdKeyIn(void) {
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	if (!stdIn || stdIn == INVALID_HANDLE_VALUE) return;
	
	for (;;) {
		WaitForSingleObject(stdIn, INFINITE);
		if (isKeyUp(stdIn)) break;
	}
	FlushConsoleInputBuffer(stdIn);
}

static inline bool
askTurnOffMonitor(void) {
	bool result = true;
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD origMode;
	GetConsoleMode(stdIn, &origMode);
	SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);
	FlushConsoleInputBuffer(stdIn);
	for (int round = kMonitorOffDelay; round > 0; --round) {
		wprintf_s(L"\rTo keep monitor on, input in %d seconds...", round);
		DWORD waitResult = WaitForSingleObject(stdIn, 1000);
		if (waitResult != WAIT_TIMEOUT) {
			result = false;
			break;
		}
	}
	SetConsoleMode(stdIn, origMode);
	FlushConsoleInputBuffer(stdIn);
	return result;
}

static inline void
monitorOff(void) {
	enum { kMonitorOff = 2 };
	SendMessageW(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, kMonitorOff);
}

int
wmain(void) {
	Command cmd = getCommand();

	if (cmd.help) {
		printHelp();
		ExitProcess(0);
	}
	
	if (!SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED)) {
		wprintf_s(L"SetThreadExecutionState failed.\n");
		ExitProcess(1);
	}
	printStatus(status_kNonSleep);

	if (!cmd.leaveMonitorOn) {
		if (askTurnOffMonitor()) {
			wprintf_s(L"\rMonitor was turned off.                   \n");
			monitorOff();
		}
		else {
			wprintf_s(L"\rMonitor was left on.                      \n");
		}
	}

	printStatus(status_kWaitingToQuit);
	waitForStdKeyIn();
	SetThreadExecutionState(ES_CONTINUOUS);
	printStatus(status_kNormal);

	ExitProcess(0);
}
