#pragma once

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
};