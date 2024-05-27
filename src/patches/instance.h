#include "../util/mem.h"
#include "../util/Hooking.Patterns.h"
#include "../util/console.h"

void patchWindowTitle()
{
	struct ClassHandler
	{
		static HWND WINAPI CreateWindowExA(
			DWORD     dwExStyle,
			LPCSTR    lpClassName,
			LPCSTR    lpWindowName,
			DWORD     dwStyle,
			int       X,
			int       Y,
			int       nWidth,
			int       nHeight,
			HWND      hWndParent,
			HMENU     hMenu,
			HINSTANCE hInstance,
			LPVOID    lpParam
		)
		{

			return CreateWindowExA(
				dwExStyle,
				lpClassName,
				lpWindowName,
				dwStyle,
				X,
				Y,
				nWidth,
				nHeight,
				hWndParent,
				hMenu,
				hInstance,
				lpParam
			);
		}
	};

	auto pattern = hook::pattern("ff 15 20 e6 78 00");
	if (pattern.size() != 1)
	{
		console::Print("Failed to find pattern for CreateWindowExA\n");
		return;
	};

	console::Print("Patching window title (%p)...\n", pattern.count(1).get(0).get<uint32_t*>(0));
	mem::WriteCalltoMemory((BYTE*)pattern.count(1).get(0).get<uint32_t*>(0), ClassHandler::CreateWindowExA, 6);
}