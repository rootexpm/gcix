#include "patches.h"

void patches::Setup() noexcept
{
	patchWindowTitle();
	patchNullSub();
	patchSteamInit();
	//patchMaxPartySize();

	console::Print("Patches applied...");
}