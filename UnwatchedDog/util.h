#pragma once
#include "includes.h"
#include <codecvt>
#include <locale>

namespace U {
	void initConsole(const LPCWSTR title);

	const std::wstring csToWstring(const char* stringToConvert);

	LPWSTR getFileVer();
}