#include "patches.h"

void patches::patchSteamInit() noexcept
{
	console::Print("Patching Steam init...");
	// write jump to skip steam init
	mem::WriteJMPtoMemory((BYTE*)0x474D7F, (void*)0x474D95,5);
}