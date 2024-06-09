#include "patches.h"

void patches::Setup() noexcept
{
	patchWindowTitle();
	//patchNullSub();
	patchDlc();
	patchMaxPartySize();

	console::Print("Patches applied...");
}