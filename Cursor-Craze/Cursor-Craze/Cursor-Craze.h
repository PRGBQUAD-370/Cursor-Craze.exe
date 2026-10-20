#pragma once

#include <Windows.h>
#include <math.h>
#include <mmsystem.h>
#define TIMER_DELAY 100
#pragma comment(lib, "winmm.lib")

#include "callbacks.h"
#include "cursors.h"
#include "desktopcopy.h"
#include "math.h"
#include "redrawdesktop.h"
#include "sounds.h"
#include "timerproc.h"

#pragma region Public Variables
extern HWND hwndDesktop;
extern HDC hdcDesktop;
extern RECT rcScrBounds;
extern HHOOK hMsgHook;
extern INT nCounter;
#pragma endregion Public Variables