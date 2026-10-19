#include "Cursor-Craze.h"

DWORD xs;
static FLOAT pfSinVals[4096];

VOID
SeedXorshift32 (
	_In_ DWORD dwSeed
)
{
	xs = dwSeed;
}

DWORD
Xorshift32 ( VOID )
{
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}