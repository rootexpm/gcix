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
