#include "hooks.h"

#include "../../ext/minhook/MinHook.h"
#include "../util/mem.h"
#include "../util/console.h"

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

	MH_CreateHook(
		reinterpret_cast<void*>(0x440FCC),
		getMapNameHook,
		reinterpret_cast<void**>(&getMapNameOg)
	);

	MH_EnableHook(MH_ALL_HOOKS);
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
	console::Print("CryptQuery being called, bypassing...");
	return true;
}

const char* __fastcall hooks::getMapNameHook(void* thisPtr, void *Unknown, unsigned __int16 a2) noexcept
{
	return "worlds\\retail01\\gothampower.wld";
}