#include "patches.h"

void patches::patchWindowTitle() noexcept
{
	struct ClassHandler
	{
		static HWND WINAPI CreateWindowExAHandler(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
		{
			lpWindowName = "Gotham City Impostors: Enhanced Edition";
			X = 0;
			Y = 0;

			return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
		}
	};

	auto pattern = hook::pattern("FF 15 D4 96 7C 00");
	if (pattern.size() != 1)
	{
		console::Print("[%s] Failed to find memory address");
		return;
	}

	console::Print("Patching window title...");

	mem::WriteCalltoMemory((BYTE*)pattern.count(1).get(0).get<uint32_t*>(0), ClassHandler::CreateWindowExAHandler, 6);
}