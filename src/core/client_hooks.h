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

	using getCertificateFn = int(__cdecl*)(int) noexcept;
	inline getCertificateFn getCertificateOg = nullptr;
	int __cdecl getCertificateHook(int a1) noexcept;

	using sub_7B50AC20Fn = int(__cdecl*)(int, const char*, size_t, int) noexcept;
	inline sub_7B50AC20Fn sub_7B50AC20Og = nullptr;
	int __cdecl sub_7B50AC20Hook(int a1, const char* a2, size_t a3, int a4) noexcept;

	using sslReadFn = int(__cdecl*)(void*, int, void*, unsigned int, void*) noexcept;
	inline sslReadFn sslReadOg = nullptr;
	int __cdecl sslReadHook(void* a1, int a2, void* a3, unsigned int a4, void* a5) noexcept;

	using sslWriteFn = int(__cdecl*)(void*, int, int, unsigned int, void*) noexcept;
	inline sslWriteFn sslWriteOg = nullptr;
	int __cdecl sslWriteHook(void* a1, int a2, int a3, unsigned int a4, void* a5) noexcept;
}