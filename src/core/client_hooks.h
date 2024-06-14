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

	using InitSSL_CtxFn = int(__cdecl*)(int, int) noexcept;
	inline InitSSL_CtxFn InitSSL_CtxOg = nullptr;
	int __cdecl InitSSL_CtxHook(int a1, int a2) noexcept;

	using setVerifyFn = int(__cdecl*)(int, int, int) noexcept;
	inline setVerifyFn setVerifyOg = nullptr;
	int __cdecl setVerifyHook(int a1, int a2, int a3) noexcept;

	using connectSslFn = int(__cdecl*)(int*, int) noexcept;
	inline connectSslFn connectSslOg = nullptr;
	int __cdecl connectSslHook(int* a1, int a2) noexcept;
}