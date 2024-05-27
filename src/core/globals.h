#pragma once
#include <cstdint>

namespace globals
{
	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandle("GameClient.dll"));
}