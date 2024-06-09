#include "hooks.h"

#include <MinHook.h>
#include "../util/mem.h"
#include "../util/console.h"
#include "../core/globals.h"
#include "../util/util.h"

#include "client_hooks.h"

DWORD WINAPI waitForDllAndHook(LPVOID lpParam)
{
	util::waitForDll("GameClient.dll");
	uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandle("GameClient.dll"));
	client_hooks::Setup(base);
	return 0;
}

void hooks::Setup() noexcept
{
	MH_Initialize();

	MH_CreateHook(
		reinterpret_cast<void*>(0x60BEC3),
		verifySignatureHook,
		reinterpret_cast<void**>(&verifySignatureOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(0x60c523),
		cryptQueryHook,
		reinterpret_cast<void**>(&cryptQueryOg)
	);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(0x440FCC),
	//	getFileNameHook,
	//	reinterpret_cast<void**>(&getFileNameOg) // client_file_mgr->GetFilename
	//);

	MH_CreateHook(
		reinterpret_cast<void*>(0x40C465),
		startShellHook,
		reinterpret_cast<void**>(&startShellOg) // StartShell
	);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(0x418833),
	//	printFileAccessHook,
	//	reinterpret_cast<void**>(&printFileAccessOg) // PrintFileAccess
	//);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(0x41A378),
	//	readAssetHook,
	//	reinterpret_cast<void**>(&readAssetOg) // ReadAsset
	//);

	MH_CreateHook(
		reinterpret_cast<void*>(0x498007),
		getMaxPartySizeHook,
		reinterpret_cast<void**>(&getMaxPartySizeOg) // GetMaxPartySize
	);

	MH_CreateHook(
		reinterpret_cast<void*>(0x4760FF),
		console::DebugPrint,
		NULL
	);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(0x668A90),
	//	getGameSettingHook,
	//	reinterpret_cast<void**>(&getGameSettingOg) // getaGameSetting
	//);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(0x60922F),
	//	dlcEnableHook,
	//	reinterpret_cast<void**>(&dlcEnableOg) // dlcEnable
	//);
	
	CreateThread(NULL, 0, waitForDllAndHook, NULL, 0, NULL);

	MH_EnableHook(MH_ALL_HOOKS);

	console::Print("Hooks applied...");
}

void hooks::Destroy() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

char __cdecl hooks::verifySignatureHook(const wchar_t* a1, int a2) noexcept
{
	console::Print("%ls being verified, bypassing...", a1);
	return true;
}

unsigned __int8 __cdecl hooks::cryptQueryHook(void* a1, int a2) noexcept
{
	console::Print("VerifyCertificate being called, bypassing...");
	return true;
}

const char* __fastcall hooks::getFileNameHook(void* thisPtr, void *Unknown, unsigned __int16 a2) noexcept
{
	const char* result = getFileNameOg(thisPtr, a2);

	console::Print("File get name: %d (%s)",a2, result);
	return result;
}

uint32 __fastcall hooks::startShellHook(void* thisPtr, void* Unknown, StartGameRequest* request) noexcept
{
	int result = startShellOg(thisPtr, request);
	return result;
}

void __cdecl hooks::printFileAccessHook(const char* a1, const char* a2) noexcept
{
	console::Print("File Access: %s: %s", a1, a2);
}

int __fastcall hooks::readAssetHook(void* thisPtr, void* Unknown, const char* a2, int a3, int a4) noexcept
{
	int result = readAssetOg(thisPtr, a2, a3, a4);
	console::Print("ReadAsset: %s", a2);
	return result;
}

unsigned int hooks::getMaxPartySizeHook() noexcept
{
	unsigned int result = getMaxPartySizeOg();
	console::Print("Max party size: %d", result);
	return result;
}

int __fastcall hooks::getGameSettingHook(void* thisPtr, void* Unknown, int a2) noexcept
{
	int result = getGameSettingOg(thisPtr, a2);
	return result;
}

int __fastcall hooks::dlcEnableHook(void* thisPtr, void* Unknown) noexcept
{
	int result = dlcEnableOg(thisPtr);
	return result;
}