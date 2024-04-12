#include "util.h"

namespace U {
    void U::initConsole(const LPCWSTR title) {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        SetConsoleTitle(title);
    }

    const std::wstring csToWstring(const char* stringToConvert) {
        std::wstring temp =
            std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(stringToConvert);
        return temp;
    }
}