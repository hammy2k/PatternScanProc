#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int Rmemcmp(const void *a, const void *b, size_t n);

uintptr_t FindPattern(uint8_t *start, size_t size, const uint8_t *pattern, size_t patternSize);

void GetAndPrintFunctionBytes(void *func, uint8_t *out, size_t count);

void* GetFPByBytes(HMODULE module, const uint8_t *sig, size_t sigSize);
