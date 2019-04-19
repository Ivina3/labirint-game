#include "win_setup.h"
#include "types.h"
/******************************************************************************
windowsVersionTest

Checks to see if have Vista/7 or earlier by attempting to retrieve function
from kernel32.dll that is only available in Vista+ version of Windows.
******************************************************************************/
int windowsVersionTest(void)
{
	/* Retrieving pointers for Windows Vista/7 Functions */
	PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetCurrentConsoleFontEx");

	/* If exists then we have Vita/7 */
	if (pGetCurrentConsoleFontEx)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/******************************************************************************
SetConsolePalette

Sets the console palette and font size.
******************************************************************************/
VOID WINAPI SetConsolePalette(COLORREF palette[], int fontX, int fontY, wchar_t *fontName)
{
	int i;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Retrieving pointers for Windows Vista/7 Functions */
	PGetCurrentConsoleFontEx pGetCurrentConsoleFontEx = (PGetCurrentConsoleFontEx)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetCurrentConsoleFontEx");
	PSetCurrentConsoleFontEx pSetCurrentConsoleFontEx = (PSetCurrentConsoleFontEx)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"), "SetCurrentConsoleFontEx");
	PGetConsoleScreenBufferInfoEx pGetConsoleScreenBufferInfoEx = (PGetConsoleScreenBufferInfoEx)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetConsoleScreenBufferInfoEx");
	PSetConsoleScreenBufferInfoEx pSetConsoleScreenBufferInfoEx = (PSetConsoleScreenBufferInfoEx)
		GetProcAddress(GetModuleHandle(L"kernel32.dll"), "SetConsoleScreenBufferInfoEx");

	/* Check for pointers: if they exist, we have Vista/7 and we can use them */
	if (pGetCurrentConsoleFontEx && pSetCurrentConsoleFontEx &&
		pGetConsoleScreenBufferInfoEx && pSetConsoleScreenBufferInfoEx)
	{
		CONSOLE_SCREEN_BUFFER_INFOEX cbi;
		CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };

		/* Tell the font info how big it is, to avoid memory corruption */
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		pGetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

		/* Set the font type to name indicated by wide string literal */
		/* Set to 0 to keep current settings */
		lstrcpyW(cfi.FaceName, fontName);
		cfi.dwFontSize.X = fontX;
		cfi.dwFontSize.Y = fontY;
		cfi.FontFamily = 0x30; /* Set to 0x30 for Terminal font */
		cfi.FontWeight = 0;

		/* Set the console font info */
		pSetCurrentConsoleFontEx(hOutput, TRUE, &cfi);

		/* Get the size of the structure before filling the struct */
		cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		pGetConsoleScreenBufferInfoEx(hOutput, &cbi);

		/* Loop through the given palette, copying the data into the color table */
		for (i = 0; i < 16; ++i)
		{
			cbi.ColorTable[i] = palette[i];
		}

		/* Set the console screen buffer info */
		pSetConsoleScreenBufferInfoEx(hOutput, &cbi);
	}
	else  /* We don't have access to the vista functions */
	{
		int i;
		CONSOLE_INFO ci = { sizeof(ci) };
		HWND hwndConsole = GetConsoleWindow();

		GetConsoleSizeInfo(&ci, hOutput);

		/* Set to 0 to keep current settings */
		ci.FontSize.X = fontX;
		ci.FontSize.Y = fontY;
		ci.FontFamily = 0; /* Set to 0x30 for Terminal font */
		ci.FontWeight = 0;

		lstrcpyW(ci.FaceName, fontName);
		ci.CursorSize = 100;
		ci.FullScreen = FALSE;
		ci.QuickEdit = FALSE;
		ci.AutoPosition = 0x10000;
		ci.InsertMode = TRUE;
		ci.ScreenColors = MAKEWORD(0x7, 0x0);
		ci.PopupColors = MAKEWORD(0x5, 0xf);
		ci.HistoryNoDup = TRUE;
		ci.HistoryBufferSize = 50;
		ci.NumberOfHistoryBuffers = 4;

		for (i = 0; i < 16; i++)
		{
			ci.ColorTable[i] = palette[i];
		}

		ci.CodePage = 0;
		ci.Hwnd = hwndConsole;
		lstrcpyW(ci.ConsoleTitle, L"");

		SetConsoleInfo(hwndConsole, &ci);
	}
}

/******************************************************************************
GetConsoleSizeInfo (XP only)

Fills up some info about the console font in the CONSOLE_INFO struct.
******************************************************************************/
static void GetConsoleSizeInfo(CONSOLE_INFO *pci, HANDLE hOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hOutput, &csbi);
	pci->ScreenBufferSize = csbi.dwSize;
	pci->WindowSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	pci->WindowSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	pci->WindowPosX = csbi.srWindow.Left;
	pci->WindowPosY = csbi.srWindow.Top;
}

/******************************************************************************
SetConsoleInfo (XP only)

Ends up sending a message to windows to reset the console info.
******************************************************************************/
BOOL SetConsoleInfo(HWND hwndConsole, CONSOLE_INFO *pci)
{
	DWORD dwConsoleOwnerPid;
	HANDLE hProcess;
	HANDLE hSection, hDupSection;
	PVOID ptrView = 0;
	HANDLE hThread;

	/* Open the process which "owns" the console */
	GetWindowThreadProcessId(hwndConsole, &dwConsoleOwnerPid);
	hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwConsoleOwnerPid);


	/* Create a SECTION object backed by page-file, then map a view of  */
	/* this section into the owner process so we can write the contents  */
	/* of the CONSOLE_INFO buffer into it  */
	hSection = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, pci->Length, 0);


	/* Copy our console structure into the section-object */
	ptrView = MapViewOfFile(hSection, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, pci->Length);
	memcpy(ptrView, pci, pci->Length);
	UnmapViewOfFile(ptrView);


	/* Map the memory into owner process  */
	DuplicateHandle(GetCurrentProcess(), hSection, hProcess, &hDupSection, 0, FALSE, DUPLICATE_SAME_ACCESS);

	/* Send console window the "update" message WM_SETCONSOLEINFO */
	SendMessage(hwndConsole, WM_SETCONSOLEINFO, (WPARAM)hDupSection, 0);

	/*clean up */
	hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)CloseHandle, hDupSection, 0, 0);
	CloseHandle(hThread);
	CloseHandle(hSection);
	CloseHandle(hProcess);
	return TRUE;
}


bool textcolorprotect = true;
/*doesn't let textcolor be the same as backgroung color if true*/



#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)

int textcolor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out, &csbi);
	int a = csbi.wAttributes;
	return a % 16;
}

int backcolor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(std_con_out, &csbi);
	int a = csbi.wAttributes;
	return (a / 16) % 16;
}

void setcolor(concol textcol, concol backcol)
{
	setcolor(int(textcol), int(backcol));
}

void setcolor(int textcol, int backcol)
{
	if (textcolorprotect)
	{
		if ((textcol % 16) == (backcol % 16))textcol++;
	}
	textcol %= 16; backcol %= 16;
	unsigned short wAttributes = ((unsigned)backcol << 4) | (unsigned)textcol;
	SetConsoleTextAttribute(std_con_out, wAttributes);
}

WORD make_attrib(unsigned foreground, unsigned background)
{
	return WORD(foreground) | (WORD(background) << 4);
}


void setup_window(const short int win_h, const short int win_w, display_t& display_settings)
{
	/* Setting the color palette to the default colors
	/* Browse MSDN for COLORREF to learn more about these RGB values */
	COLORREF palette[16] =
	{
		0x0022B14C, 0x003333ff, 0x0033ff33, 0x00d5bfd7,
		0x00e970dd, 0x00ffff0f, 0x002fffff, 0x00c0c0c0,
		0x08ed2603, 0x00000000, 0x0000ff00, 0x00ffff00,
		0x00ff0080, 0x00ff00ff, 0x0000ffff, 0x00ffffff,

	};
	/* Search MSDN for the RGB macro to easily generate COLORREF values */
	//SetConsolePalette(palette, 43, 72, L"Lucida Console");
	SetConsolePalette(palette, 12, 16, L"Consolas");

	//printf("Huge Lucida!\n");
	//getchar();


	/*for (int i = 0; i <= 15; i++)
	{
	setcolor(i, black);
	printf("color %d ", i);
	}
	printf("\n");*/
	/* Window size coordinates, be sure to start index at zero! */
	SMALL_RECT windowSize = { 0, 0, win_w - 1, win_h - 1 };

	/* A COORD struct for specificying the console's screen buffer dimensions */
	display_settings.bufferSize = { win_w, win_h };
	/* Setting up different variables for passing to WriteConsoleOutput */
	display_settings.characterBufferSize = { win_w, win_h };
	display_settings.characterPosition = { 0, 0 };
	display_settings.consoleWriteArea = { 0, 0, win_w - 1, win_h - 1 };


	/* A CHAR_INFO structure containing data about a single character */
	display_settings.consoleBuffer = new CHAR_INFO[win_h*win_w];

	/* initialize handles */
	display_settings.wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	display_settings.rHnd = GetStdHandle(STD_INPUT_HANDLE);

	/* Set the console's title */
	SetConsoleTitle(L"Our shiny new title!");

	/* Set the window size */
	SetConsoleWindowInfo(display_settings.wHnd, TRUE, &windowSize);

	/* Set the screen's buffer size */
	SetConsoleScreenBufferSize(display_settings.wHnd, display_settings.bufferSize);

}