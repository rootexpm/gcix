#pragma once
#include "../monolith/StartGameRequest.h"

namespace hooks
{
	void Setup() noexcept;
	void Destroy() noexcept;

	using verifySignatureFn = char(__cdecl*)(const wchar_t*, int) noexcept;
	inline verifySignatureFn verifySignatureOg = nullptr;
	char __cdecl verifySignatureHook(const wchar_t* a1, int a2) noexcept;

	using cryptQueryFn = unsigned __int8(__cdecl*)(void*, int) noexcept;
	inline cryptQueryFn cryptQueryOg = nullptr;
	unsigned __int8 __cdecl cryptQueryHook(void* a1, int a2) noexcept;

	using getFileNameFn = char*(__thiscall*)(void*, unsigned __int16) noexcept;
	inline getFileNameFn getFileNameOg = nullptr;
	const char* __fastcall getFileNameHook(void* thisPtr, void* Unknown, unsigned __int16 a2) noexcept;

	using startShellFn = uint32(__thiscall*)(void*, StartGameRequest*) noexcept;
	inline startShellFn startShellOg = nullptr;
	uint32 __fastcall startShellHook(void* thisPtr, void* Unknown, StartGameRequest* request) noexcept;
};