#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>

#include "core/hooks.h"
#include "util/console.h"
#include "patches/patches.h"

//DWORD WINAPI Setup(LPVOID instance)
//{
//	//Setup console...
//	console::Setup();
//
//	// Setup hooks...
//	hooks::Setup();
//
//	// Setup patches
//	patches::Setup();
//
//	while (!GetAsyncKeyState(VK_END))
//		std::this_thread::sleep_for(std::chrono::milliseconds(200));
//
//	console::Destroy();
//	hooks::Destroy();
//
//	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), EXIT_SUCCESS);
//}

BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);
		
		console::Setup();
		patches::Setup();
		hooks::Setup();
		
		console::Print("Setup completed");
	}

	return TRUE;
}