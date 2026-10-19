#include "Cursor-Craze.h"

VOID
WINAPI 
Redrawer 
( VOID ) 
{

    for (;;)
    {
        RedrawWindow (
            NULL,
            NULL,
            NULL,
            RDW_INVALIDATE |
            RDW_ERASE |
            RDW_ALLCHILDREN |
            RDW_UPDATENOW
        );
        Sleep ( 2000 );
    }
}