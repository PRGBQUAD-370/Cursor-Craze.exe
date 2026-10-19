#include "Cursor-Craze.h"

VOID 
WINAPI 
sound 
( VOID ) 
{

    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen ( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );

    const DWORD bufferSize = 11025 * 180;
    char* buffer = (char*)HeapAlloc ( GetProcessHeap ( ), HEAP_ZERO_MEMORY, bufferSize );
    if (!buffer) { waveOutClose ( hWaveOut ); return; }

    for (DWORD t = 0; t < bufferSize; ++t)

        buffer[t] = ( BYTE ) ( (t * (t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7)) );

    WAVEHDR header = { 0 };
    header.lpData = buffer;
    header.dwBufferLength = bufferSize;

    waveOutPrepareHeader ( hWaveOut, &header, sizeof ( WAVEHDR ) );
    waveOutWrite ( hWaveOut, &header, sizeof ( WAVEHDR ) );

    waveOutUnprepareHeader ( hWaveOut, &header, sizeof ( WAVEHDR ) );
    waveOutClose ( hWaveOut );

}