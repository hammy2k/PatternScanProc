#include "GetModuleHandle.h"

wchar_t RtolowerW(wchar_t c) {
    if (c >= L'A' && c <= L'Z')
        return c + 32;
    return c;
}

int RlstrcmpiW(const wchar_t* a, const wchar_t* b) {
    while (*a && *b) {
        wchar_t c1 = RtolowerW(*a);
        wchar_t c2 = RtolowerW(*b);
        if (c1 != c2)
            return c1 - c2;
        ++a; ++b;
    }
    return *a - *b;
}

BOOL IsStringEqual(LPCWSTR a, LPCWSTR b) {
    if (!a || !b) return FALSE;
    return RlstrcmpiW(a, b) == 0;
}

HMODULE RGetModuleHandle(LPCWSTR szModuleName) {

#ifdef _WIN64
    PPEB pPeb = (PPEB)__readgsqword(0x60);
#else
    PPEB pPeb = (PPEB)__readfsdword(0x30);
#endif

    if (!pPeb || !pPeb->Ldr)
        return NULL;

    PPEB_LDR_DATA pLdr = pPeb->Ldr;

    PLIST_ENTRY head = &pLdr->InMemoryOrderModuleList;
    PLIST_ENTRY curr = head->Flink;

    if (szModuleName == NULL) {
        PLDR_DATA_TABLE_ENTRY exeEntry =
            CONTAINING_RECORD(curr, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
        return (HMODULE)exeEntry->DllBase;
    }

    while (curr != head) {

        PLDR_DATA_TABLE_ENTRY entry =
            CONTAINING_RECORD(curr, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (entry->BaseDllName.Buffer) {
            if (IsStringEqual(entry->BaseDllName.Buffer, szModuleName)) {
                wprintf(L"[+] Found DLL: %s\n", entry->BaseDllName.Buffer);
                return (HMODULE)entry->DllBase;
            }
        }

        curr = curr->Flink;
    }

    return NULL;
}
