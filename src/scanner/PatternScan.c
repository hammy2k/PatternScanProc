#include "PatternScan.h"

int Rmemcmp(const void *a, const void *b, size_t n) {
    const uint8_t *p1 = a;
    const uint8_t *p2 = b;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] - p2[i];
    }
    return 0;
}

uintptr_t FindPattern(uint8_t *start, size_t size,
                      const uint8_t *pattern, size_t patternSize) {
    for (size_t i = 0; i <= size - patternSize; i++) {
        if (Rmemcmp(start + i, pattern, patternSize) == 0)
            return (uintptr_t)(start + i);
    }
    return 0;
}

void GetAndPrintFunctionBytes(void *func, uint8_t *out, size_t count) {
    uint8_t *p = (uint8_t *)func;

    printf("Function bytes @ %p: ", func);
    for (size_t i = 0; i < count; i++) {
        out[i] = p[i];
        printf("%02X ", out[i]);
    }
    printf("\n");
}

void* GetFPByBytes(HMODULE module, const uint8_t *sig, size_t sigSize) {

    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)module;
    PIMAGE_NT_HEADERS nt =
        (PIMAGE_NT_HEADERS)((uint8_t*)module + dos->e_lfanew);

    uint8_t *codeBase =
        (uint8_t*)module + nt->OptionalHeader.BaseOfCode;

    size_t codeSize =
        nt->OptionalHeader.SizeOfCode;

    return (void*)FindPattern(codeBase, codeSize, sig, sigSize);
}
