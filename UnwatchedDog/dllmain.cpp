/* 
Patches the CP77 watchdog exitproc jump
I have no idea what the consequences of this are !
It shouldn't force itself to crash when PT photomode takes > 120 seconds to render
*/
#include "includes.h"
#include "mem.h"
#include "util.h"

DWORD Patch() {
    #ifdef _DEBUG
        U::initConsole(L"CP77 Debug");
    #endif

    // Watchdog exitproc 2.12a
    if (M::PatternPatch("74 2F 8B 05 ? ? ? ?", "Cyberpunk2077.exe", "\xEB", 1, 0)) {
        MessageBoxW(NULL, L"Watchdog was patched!\n\nBe careful, this could have\nunintended consequences!", L"UnwatchedDog", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
    }

	return NULL;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Patch, 0, 0, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}