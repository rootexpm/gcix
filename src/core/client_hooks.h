#pragma once
#include "cstdint"

namespace client_hooks
{
	void Setup(uintptr_t globalAddress) noexcept;
	void Destroy() noexcept;

	using setGameSettingsFn = int(__stdcall*)(int) noexcept;
	inline setGameSettingsFn setGameSettingsOg = nullptr;
	int __stdcall setGameSettingsHook(int a1) noexcept;
}