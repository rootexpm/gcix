#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>

#include "core/hooks.h"
#include "util/console.h"
#include "patches/patches.h"
#include "steam/steam.h"

BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		
#ifdef DEBUG
		console::Setup();
#endif
		patches::Setup();
		hooks::Setup();
		
		console::Print("Setup completed");
	}

	return TRUE;
}