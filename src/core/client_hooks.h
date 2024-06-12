#pragma once
#include "cstdint"

namespace client_hooks
{
	void Setup(uintptr_t globalAddress) noexcept;
	void Destroy() noexcept;

	using setGameSettingsFn = int(__stdcall*)(int) noexcept;
	inline setGameSettingsFn setGameSettingsOg = nullptr;
	int __stdcall setGameSettingsHook(int a1) noexcept;

	using getBaseServerFn = char*(__thiscall*)(void*) noexcept;
	inline getBaseServerFn getBaseServerOg = nullptr;
	char* __fastcall getBaseServerHook(void* thisPtr, void* Unknown) noexcept;

	using sslConnectFn = int(__cdecl*)(int, int) noexcept;
	inline sslConnectFn sslConnectOg = nullptr;
	int __cdecl sslConnectHook(int a1, int a2) noexcept;
}