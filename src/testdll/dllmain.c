#include <windows.h>
#include <stdio.h>
#include <stdint.h>

static int HiddenFunction(int x, int y)
{
    return x * y + 5;
}

static int AnotherHiddenFunction(void)
{
    return 42;
}

__declspec(dllexport)
int NotHidden(void)
{
    return 67;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD     fdwReason,
                    LPVOID    lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

    }

    return TRUE;
}
