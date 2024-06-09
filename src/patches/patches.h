#pragma once

#include "../util/Hooking.Patterns.h"
#include "../util/mem.h"
#include "../util/console.h"

namespace patches
{
	void Setup() noexcept;
	void patchWindowTitle() noexcept;
	void patchMaxPartySize() noexcept;
	void patchNullSub() noexcept;
	void patchSteamInit() noexcept;
	void patchDlc() noexcept;
}