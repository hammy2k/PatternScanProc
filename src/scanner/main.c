#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "GetModuleHandle.h"
#include "PatternScan.h"

uint8_t sigHidden[12] = {0x55, 0x48, 0x89, 0xE5, 0x89, 0x4D, 0x10, 0x89, 0x55, 0x18, 0x8B, 0x45};
uint8_t sigAnother[6] = {0x55, 0x48, 0x89, 0xE5, 0xB8, 0x2A};   

int main(void) {
    HMODULE hiddendll  = LoadLibrary("hidden.dll");

    void *foundHidden  = GetFPByBytes(hiddendll, sigHidden, sizeof(sigHidden));
    void *foundAnother = GetFPByBytes(hiddendll, sigAnother, sizeof(sigAnother));

    printf("Scan HiddenFunction  : %p\n", foundHidden);
    printf("Scan AnotherFunction : %p\n\n", foundAnother);

    typedef int (*HiddenFn_t)(int, int);
    typedef int (*AnotherFn_t)(void);

    HiddenFn_t  hfn = (HiddenFn_t)foundHidden;
    AnotherFn_t afn = (AnotherFn_t)foundAnother;

    printf("HiddenFunction(3,7) = %d\n", hfn(3, 7));
    printf("AnotherFunction()  = %d\n", afn());

    return 0;
}
