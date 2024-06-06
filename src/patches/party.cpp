#include "patches.h"

void patches::patchMaxPartySize() noexcept
{
	console::Print("Patching max party size...");
	mem::UpdateMemoryAddress((void*)0x4980BD, "\x6A\x01", 2);
	mem::UpdateMemoryAddress((void*)0x4980D9, "\x83\x7D\x68\x01", 4);
}