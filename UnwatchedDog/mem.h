#pragma once
#include "includes.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )      (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )      (getBits(x[0]) << 4 | getBits(x[1]))

namespace M {
	ULONG_PTR FindPattern(const char* szModule, const char* szSignature);

	void WriteMem(uintptr_t dst, const char* src, int idx);

	int PatternPatch(const char* pat, const char* module, const char* src, int size, int idx);
}