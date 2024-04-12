#include "mem.h"
#include "util.h"

namespace M {
	DWORD_PTR M::FindPattern(const char* szModule, const char* szSignature) {
		MODULEINFO inf;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &inf, sizeof(MODULEINFO));
		
		DWORD_PTR begin = (DWORD_PTR)GetModuleHandleA(szModule);
		DWORD_PTR end = (begin + (DWORD_PTR)inf.SizeOfImage);
		DWORD_PTR first = 0;
		const char* pat = szSignature;

		for (DWORD_PTR cur = begin; cur < end; cur++) {
			if (!*pat) return first;
			if (*(PBYTE)pat == ('\?') || *(BYTE*)cur == getByte(pat)) {
				if (!first) { 
					first = cur;
				}
				if (!pat[2]) { 
					return first; 
				}
				if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) { 
					pat += 3; 
				}
				else pat += 2;
			}
			else {
				pat = szSignature;
				first = 0;
			}
		}
		return NULL;
	}

	void M::WriteMem(uintptr_t dst, const char* src, int idx) {
		unsigned long prev;
		VirtualProtect((LPVOID)(dst), idx, PAGE_EXECUTE_READWRITE, &prev);
		memcpy((LPVOID)dst, src, idx);
	}

	int M::PatternPatch(const char* pat, const char* module, const char* src, int size, int idx) {
		DWORD_PTR pVar = FindPattern(module, pat);
		pVar += idx;
		if (pVar != 0) {
			M::WriteMem(pVar, src, size);
			return 1;
		}

		else {
			std::wstring t = U::csToWstring(pat);
			std::wstring c = L"Error in PatternPatch()\nPattern wasn't found\n\n" + t;
			#ifdef _DEBUG
				std::wcout << c << std::endl;
			#endif
			LPCWSTR out = c.c_str();
			MessageBoxW(NULL, out, L"UnwatchedDog", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
			return 0;
		}
	}
}
