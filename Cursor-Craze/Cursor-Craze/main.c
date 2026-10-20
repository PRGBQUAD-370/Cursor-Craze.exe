#include "Cursor-Craze.h"

HWND hwndDesktop;
HDC hdcDesktop;
RECT rcScrBounds;
HHOOK hMsgHook;
INT nCounter;

VOID
WINAPI
Initialize ( VOID )
{

	HMODULE hModUser32 = LoadLibraryW ( L"user32.dll" );
	BOOL ( WINAPI * SetProcessDPIAware )(VOID) = (BOOL ( WINAPI* )(VOID))GetProcAddress ( hModUser32, "SetProcessDPIAware" );
	if (SetProcessDPIAware)
		SetProcessDPIAware ( );
	FreeLibrary ( hModUser32 );

	hwndDesktop = HWND_DESKTOP;
	hdcDesktop = GetDC ( hwndDesktop );

	SeedXorshift32 ( (DWORD)__rdtsc ( ) );
	EnumDisplayMonitors ( NULL, NULL, &MonitorEnumProc, 0 );
	CloseHandle ( CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)TimerThread, NULL, 0, NULL ) );

}

INT
WINAPI
wWinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pszCmdLine,
	_In_ INT nShowCmd
)
{
	UNREFERENCED_PARAMETER ( hInstance );
	UNREFERENCED_PARAMETER ( hPrevInstance );
	UNREFERENCED_PARAMETER ( pszCmdLine );
	UNREFERENCED_PARAMETER ( nShowCmd );

	HANDLE hAudioThread, hCursorDraw, hDesktopCopy, hRedrawDesktop;

	Initialize ( );

	if (MessageBoxW ( NULL, L"Cursor-Craze.exe, Do you want to spawn cursors randomly all over the screen?\r\nIf you want to then press yes to continue", L"Cursor-Craze.exe", MB_YESNO | MB_ICONWARNING ) != IDYES) {
		ExitProcess ( 0 );
	}

	if (MessageBoxW ( NULL, L"Are you sure?\r\nFinal Chance to close it", L"Cursor-Craze.exe", MB_YESNO | MB_ICONWARNING ) != IDYES) {
		ExitProcess ( 0 );
	}

	Sleep ( 1000 );

	hAudioThread = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)sound, NULL, 0, NULL );
	hCursorDraw = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)CursorDraw, NULL, 0, NULL );
	hDesktopCopy = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)DesktopCopyBlt, NULL, 0, NULL );
	hRedrawDesktop = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)Redrawer, NULL, 0, NULL );

	Sleep ( 180000 );

	TerminateThread ( hAudioThread, 0 );
	CloseHandle ( hAudioThread );

	TerminateThread ( hCursorDraw, 0 );
	CloseHandle ( hCursorDraw );

	TerminateThread ( hDesktopCopy, 0 );
	CloseHandle ( hDesktopCopy );

	TerminateThread ( hRedrawDesktop, 0 );
	CloseHandle ( hRedrawDesktop );

}