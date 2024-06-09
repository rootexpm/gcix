#ifdef _DEBUG
#define DEBUG true
#endif

#include "console.h"

#include <Windows.h>
#include <cstdio>

void console::Setup() noexcept
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);

	char title[256];
	sprintf_s(title, sizeof(title), "gcix - %s %s", __DATE__, __TIME__);
	SetConsoleTitleA(title);
}

void console::Destroy() noexcept
{
	fclose(reinterpret_cast<FILE*>(stdout));
	fclose(reinterpret_cast<FILE*>(stdin));
	fclose(reinterpret_cast<FILE*>(stderr));
	FreeConsole();
}

void console::Print(const char* format, ...) noexcept
{
	va_list args;
	va_start(args, format);

	printf_s("[gcix] ");
	vprintf_s(format, args);
	printf_s("\n");

	va_end(args);
}