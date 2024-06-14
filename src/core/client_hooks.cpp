#include "client_hooks.h"
#include "MinHook.h"
#include "../util/console.h"
#include "../util/mem.h"

uintptr_t lglobalAddress = 0;

void client_hooks::Setup(uintptr_t globalAddress) noexcept
{
	console::Print("Initializing client hooks: %p", globalAddress);
	
	lglobalAddress = globalAddress;

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x13c030),
		setGameSettingsHook,
		reinterpret_cast<void**>(&setGameSettingsOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x5a5e40),
		getBaseServerHook,
		reinterpret_cast<void**>(&getBaseServerOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x582f40),
		console::DebugPrint,
		NULL
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x579d00), // custom function to print curl logs
		console::AgoraPrint,
		NULL
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x64a1c0),
		setVerifyHook,
		reinterpret_cast<void**>(&setVerifyOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x6a6c80),
		connectSslHook,
		reinterpret_cast<void**>(&connectSslOg)
	);

	// nopping calls below to prevent console being flooded by useless logs
	mem::Nop((BYTE*)lglobalAddress + 0x64996f, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x648226, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x649606, 5);
	//mem::UpdateMemoryAddress((void*)(lglobalAddress + 0x59ddfa), "\x68\xb3\x15\00\x00", 5); // change port to 5555

	MH_EnableHook(MH_ALL_HOOKS);

	console::Print("Client hooks initialized");
}

int __stdcall client_hooks::setGameSettingsHook(int a1) noexcept
{
	console::Print("Setting min players to 2");

	int result = setGameSettingsOg(a1);

	int MinRankedMatchPlayers = 2; 
	void* address = reinterpret_cast<void*>(lglobalAddress + 0x813c1c); // address of MinRankedMatchPlayers @VZP
	mem::UpdateMemoryAddress(address, &MinRankedMatchPlayers, sizeof(MinRankedMatchPlayers));
	
	return result;
}

char* __fastcall client_hooks::getBaseServerHook(void* thisPtr, void* Unknown) noexcept
{
	static char url[] = "127.0.0.1";
	return url;
}

int __cdecl client_hooks::InitSSL_CtxHook(int ctx, int a2) noexcept
{
	int result = InitSSL_CtxOg(ctx, a2);
	*(BYTE*)(ctx + 236) = 0; //verifyPeer
	*(BYTE*)(ctx + 237) = 1; // verifyNone

	return result;
}

int __cdecl client_hooks::setVerifyHook(int a1, int a2, int a3) noexcept
{
	console::Print("SET VERIFY %d", a2);
						//SSL_VERIFY_NONEqww
	return setVerifyOg(a1, 0, a3);
}

int __cdecl client_hooks::connectSslHook(int* a1, int a2) noexcept
{
	int v6 = *a1;
	*(DWORD*)(v6 + 544) = 0; // verifyPeer

	int result = connectSslOg(a1, a2);
	return result;
}
