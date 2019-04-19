#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>

#define WM_SETCONSOLEINFO (WM_USER+201) 
#pragma pack(push, 1) 
typedef struct _CONSOLE_INFO
{
	ULONG Length;
	COORD ScreenBufferSize;
	COORD WindowSize;
	ULONG WindowPosX;
	ULONG WindowPosY;
	COORD FontSize;
	ULONG FontFamily;
	ULONG FontWeight;
	WCHAR FaceName[32];
	ULONG CursorSize;
	ULONG FullScreen;
	ULONG QuickEdit;
	ULONG AutoPosition;
	ULONG InsertMode;
	USHORT ScreenColors;
	USHORT PopupColors;
	ULONG HistoryNoDup;
	ULONG HistoryBufferSize;
	ULONG NumberOfHistoryBuffers;
	COLORREF ColorTable[16];
	ULONG CodePage;
	HWND Hwnd;
	WCHAR ConsoleTitle[0x100];
} CONSOLE_INFO;
#pragma pack(pop) 

typedef struct CONSOLE_FONT
{
	DWORD index;
	COORD dimension;
} CONSOLE_FONT;

//struct _CONSOLE_FONT_INFOEX {
//	ULONG cbSize;
//	DWORD nFont;
//	COORD dwFontSize;
//	UINT  FontFamily;
//	UINT  FontWeight;
//	WCHAR FaceName[LF_FACESIZE];
//};
//
//typedef _CONSOLE_FONT_INFOEX CONSOLE_FONT_INFOEX;
//typedef _CONSOLE_FONT_INFOEX* PCONSOLE_FONT_INFOEX;

//typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
//	ULONG      cbSize;
//	COORD      dwSize;
//	COORD      dwCursorPosition;
//	WORD       wAttributes;
//	SMALL_RECT srWindow;
//	COORD      dwMaximumWindowSize;
//	WORD       wPopupAttributes;
//	BOOL       bFullscreenSupported;
//	COLORREF   ColorTable[16];
//} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;

typedef BOOL(WINAPI *PGetCurrentConsoleFontEx)(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
typedef BOOL(WINAPI *PSetCurrentConsoleFontEx)(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
typedef BOOL(WINAPI *PGetConsoleScreenBufferInfoEx)(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);
typedef BOOL(WINAPI *PSetConsoleScreenBufferInfoEx)(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);

typedef BOOL(WINAPI *PSetConsoleFont)(HANDLE, DWORD);
typedef BOOL(WINAPI *PGetConsoleFontInfo)(HANDLE, BOOL, DWORD, CONSOLE_FONT*);
typedef int (WINAPI *PGetNumberOfConsoleFonts)();

BOOL SetConsoleInfo(HWND hwndConsole, CONSOLE_INFO *pci);
VOID WINAPI SetConsolePalette(COLORREF palette[], int fontX, int fontY, wchar_t *fontName);
static void GetConsoleSizeInfo(CONSOLE_INFO *pci, HANDLE hOutput);
int windowsVersionTest(void);

WORD make_attrib(unsigned foreground, unsigned background);

enum concol
{
	black = 0,
	dark_blue = 1,
	dark_green = 2,
	dark_aqua, dark_cyan = 3,
	dark_red = 4,
	dark_purple = 5, dark_pink = 5, dark_magenta = 5,
	dark_yellow = 6,
	dark_white = 7,
	gray = 8,
	blue = 9,
	green = 10,
	aqua = 11, cyan = 11,
	red = 12,
	purple = 13, pink = 13, magenta = 13,
	yellow = 14,
	white = 15
};

void setcolor(concol textcolor, concol backcolor);
void setcolor(int textcolor, int backcolor);
int textcolor();/*returns current text color*/
int backcolor();/*returns current background color*/

struct display_t;
void setup_window(const short int win_h, const short int win_w, display_t& display_settings);