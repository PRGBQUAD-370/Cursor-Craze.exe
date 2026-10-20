#include "Cursor-Craze.h"

VOID
WINAPI
DesktopCopyBlt
( VOID )
{

	HDC hdc;
	int w = GetSystemMetrics ( 0 );
	int h = GetSystemMetrics ( 1 );
	while (1) {
		hdc = GetDC ( 0 );
		BitBlt ( hdc, rand ( ) % 1, rand ( ) % 1, w, h, hdc, rand ( ) % 1, rand ( ) % 1, SRCCOPY );
		Sleep ( 1000 );
		ReleaseDC ( 0, hdc );

	}
}