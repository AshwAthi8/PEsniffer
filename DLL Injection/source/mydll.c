
#include<windows.h>
void callmedude();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  fwdreason,
                       LPVOID lpReserved
                     )
{
    switch (fwdreason)
    {
    case DLL_PROCESS_ATTACH:
        callmedude();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void callmedude() {
    MessageBoxA(0, "lol", "injected", 0);
    
}