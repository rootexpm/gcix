#include "util.h"
#include "windows.h"

bool util::isDllLoaded(const char* dllName) noexcept
{
	return GetModuleHandleA(dllName);
}

void util::waitForDll(const char* dllName) noexcept
{
	while (!isDllLoaded(dllName))
		Sleep(100);
}
