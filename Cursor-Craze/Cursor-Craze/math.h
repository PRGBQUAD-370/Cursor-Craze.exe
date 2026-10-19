#pragma once
#include "Cursor-Craze.h"

VOID
SeedXorshift32 (
	_In_ DWORD dwSeed
);

DWORD
Xorshift32 
( VOID );