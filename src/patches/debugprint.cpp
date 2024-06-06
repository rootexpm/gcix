#include "patches.h"

void patches::patchNullSub() noexcept
{
	console::Print("Patching nullsub...");
	//mem::UpdateMemoryAddress((void*)0x48CA7F, "\x90\x90\x90\xC3", 5);
}