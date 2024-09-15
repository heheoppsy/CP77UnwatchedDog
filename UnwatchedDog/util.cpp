#include "util.h"

namespace U {
    void initConsole(const LPCWSTR title) {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        SetConsoleTitle(title);
    }

    const std::wstring csToWstring(const char* stringToConvert) {
        std::wstring temp =
            std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(stringToConvert);
        return temp;
    }

    LPWSTR getFileVer() {
        LPWSTR strResult{};
        wchar_t szModPath[MAX_PATH];
        szModPath[0] = L'\0';
        GetModuleFileName(NULL, szModPath, sizeof(szModPath));
        DWORD dwHandle;
        DWORD dwSize = GetFileVersionInfoSize(szModPath, &dwHandle);

        if (dwSize > 0) {
            BYTE* pbBuf = static_cast<BYTE*>(alloca(dwSize));
            if (GetFileVersionInfo(szModPath, dwHandle, dwSize, pbBuf)) {
                UINT uiSize;
                BYTE* lpb;
                if (VerQueryValue(pbBuf,L"\\VarFileInfo\\Translation",(void**)&lpb,&uiSize)) {
                    WORD* lpw = (WORD*)lpb;
                    CString strQuery;
                    strQuery.Format(L"\\StringFileInfo\\%04x%04x\\ProductVersion", lpw[0], lpw[1]);
                    if (VerQueryValue(pbBuf, const_cast<LPWSTR>((LPCWSTR)strQuery), (void**)&lpb, &uiSize) && uiSize > 0) {
                        strResult = (wchar_t*)lpb;
                    }
                }
            }
        }
        return strResult;
    }
}