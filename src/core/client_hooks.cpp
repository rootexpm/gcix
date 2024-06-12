#include "client_hooks.h"
#include "MinHook.h"
#include "../util/console.h"
#include "../util/mem.h"

uintptr_t lglobalAddress = 0;

const char* cert = R"(-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----)"; // cert here

void client_hooks::Setup(uintptr_t globalAddress) noexcept
{
	console::Print("Initializing client hooks: %p", globalAddress);
	
	lglobalAddress = globalAddress;

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x13c030),
		setGameSettingsHook,
		reinterpret_cast<void**>(&setGameSettingsOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x5a5e40),
		getBaseServerHook,
		reinterpret_cast<void**>(&getBaseServerOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x582f40),
		console::DebugPrint,
		NULL
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x579d00), // custom function to print curl logs
		console::AgoraPrint,
		NULL
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x6a6ef0), // skip CyaSSL connect..
		sslConnectHook,
		reinterpret_cast<void**>(&sslConnectOg)
	);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(lglobalAddress + 0x649b60),
	//	getCertificateHook,
	//	reinterpret_cast<void**>(&getCertificateOg)
	//);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(lglobalAddress + 0x64ac20),
	//	sub_7B50AC20Hook,
	//	reinterpret_cast<void**>(&sub_7B50AC20Og)
	//);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(lglobalAddress + 0x6a71f0),
	//	sslReadHook,
	//	reinterpret_cast<void**>(&sslReadOg)
	//);

	//MH_CreateHook(
	//	reinterpret_cast<void*>(lglobalAddress + 0x6a7100),
	//	sslWriteHook,
	//	reinterpret_cast<void**>(&sslWriteOg)
	//);

	// nopping calls below to prevent console being flooded by useless logs
	mem::Nop((BYTE*)lglobalAddress + 0x64996f, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x648226, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x649606, 5);

	MH_EnableHook(MH_ALL_HOOKS);

	console::Print("Client hooks initialized");
}

int __stdcall client_hooks::setGameSettingsHook(int a1) noexcept
{
	console::Print("Setting min players to 2");

	int result = setGameSettingsOg(a1);

	int MinRankedMatchPlayers = 2; 
	void* address = reinterpret_cast<void*>(lglobalAddress + 0x813c1c); // address of MinRankedMatchPlayers @VZP
	mem::UpdateMemoryAddress(address, &MinRankedMatchPlayers, sizeof(MinRankedMatchPlayers));
	
	return result;
}

char* __fastcall client_hooks::getBaseServerHook(void* thisPtr, void* Unknown) noexcept
{
	static char url[] = "127.0.0.1";
	return url;
}

// SSL offset 649b6d
int __cdecl client_hooks::sslConnectHook(int a1, int a2) noexcept
{
	// idek
	DWORD v6 = a1 + 20 * a2 + 320;
	*(DWORD*)(v6 + 12) = 10;
	*(DWORD*)(v6 + 16) = 4;
	int result = sslConnectOg(a1, a2);
	return result;
}

int __cdecl client_hooks::getCertificateHook(int a1) noexcept
{
	if (a1 == 0)
		return 0;

	int v5 = 1;
	const char* Str = cert;

	while (v5 == 1 && Str)
	{
		size_t v1 = std::strlen(Str);
		v5 = sub_7B50AC20Og(a1, Str, v1, 1);
		if (v5 == 1)
		{
			const char* v2 = std::strstr(Str, "-----END CERTIFICATE-----");
			Str = std::strstr(v2, "-----BEGIN CERTIFICATE-----");
		}
	}
	return v5;
}

int __cdecl client_hooks::sub_7B50AC20Hook(int a1, const char* a2, size_t a3, int a4) noexcept
{
	return 0;
}

int __cdecl client_hooks::sslReadHook(void* a1, int a2, void* a3, unsigned int a4, void* a5) noexcept
{

	a5 = 0;
	return a4;
}

int __cdecl client_hooks::sslWriteHook(void* a1, int a2, int a3, unsigned int a4, void* a5) noexcept
{
	a5 = 0;
	return a4;
}