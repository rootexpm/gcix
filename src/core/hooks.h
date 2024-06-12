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

	using printFileAccessFn = void(__cdecl*)(const char* a1, const char*) noexcept;
	inline printFileAccessFn printFileAccessOg = nullptr;
	void __cdecl printFileAccessHook(const char* a1, const char* a2) noexcept;

	using readAssetFn = int(__thiscall*)(void*, const char*, int, int) noexcept;
	inline readAssetFn readAssetOg = nullptr;
	int __fastcall readAssetHook(void* thisPtr, void* Unknown, const char* a2, int a3, int a4) noexcept;

	using getMaxPartySizeFn = unsigned int(*)() noexcept;
	inline getMaxPartySizeFn getMaxPartySizeOg = nullptr;
	unsigned int getMaxPartySizeHook() noexcept;

	using getGameSetting = int(__thiscall*)(void*, int) noexcept;
	inline getGameSetting getGameSettingOg = nullptr;
	int __fastcall getGameSettingHook(void* thisPtr, void* Unknown, int a2) noexcept;

	using dlcEnableFn = int(__thiscall*)(void*) noexcept;
	inline dlcEnableFn dlcEnableOg = nullptr;
	int __fastcall dlcEnableHook(void* thisPtr, void* Unknown) noexcept;

	using startSessionFn = int(__thiscall*)(void*) noexcept;
	inline startSessionFn startSessionOg = nullptr;
	int __fastcall startSessionHook(void* thisPtr, void* Unknown) noexcept;

	using initTclFn = void(__thiscall*)(char*) noexcept;
	inline initTclFn initTclOg = nullptr;
	void __fastcall initTclHook(char* thisPtr, void* Unknown) noexcept;

	using patchWbid = int(*)(int a1, int ArgList, char* Source) noexcept;
	inline patchWbid patchWbidOg = nullptr;
	int __cdecl patchWbidHook(int a1, int ArgList, char* Source) noexcept;

	using verifyWbid = int(*)(int) noexcept;
	inline verifyWbid verifyWbidOg = nullptr;
	int __fastcall verifyWbidHook(int a1) noexcept;
};