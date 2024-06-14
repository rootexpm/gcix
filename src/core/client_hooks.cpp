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
		reinterpret_cast<void*>(lglobalAddress + 0x64a1c0),
		setVerifyHook,
		reinterpret_cast<void**>(&setVerifyOg)
	);

	MH_CreateHook(
		reinterpret_cast<void*>(lglobalAddress + 0x6a6c80),
		connectSslHook,
		reinterpret_cast<void**>(&connectSslOg)
	);

	// nopping calls below to prevent console being flooded by useless logs
	mem::Nop((BYTE*)lglobalAddress + 0x64996f, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x648226, 5);
	mem::Nop((BYTE*)lglobalAddress + 0x649606, 5);
	//mem::UpdateMemoryAddress((void*)(lglobalAddress + 0x59ddfa), "\x68\xb3\x15\00\x00", 5); // change port to 5555

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

enum { /* ssl Constants */
	SSL_ERROR_NONE = 0,   /* for most functions */
	SSL_FAILURE = 0,   /* for some functions */
	SSL_SUCCESS = 1,

	SSL_BAD_CERTTYPE = -8,
	SSL_BAD_STAT = -7,
	SSL_BAD_PATH = -6,
	SSL_BAD_FILETYPE = -5,
	SSL_BAD_FILE = -4,
	SSL_NOT_IMPLEMENTED = -3,
	SSL_UNKNOWN = -2,
	SSL_FATAL_ERROR = -1,

	SSL_FILETYPE_ASN1 = 2,
	SSL_FILETYPE_PEM = 1,
	SSL_FILETYPE_DEFAULT = 2, /* ASN1 */
	SSL_FILETYPE_RAW = 3, /* NTRU raw key blob */

	SSL_VERIFY_NONE = 0,
	SSL_VERIFY_PEER = 1,
	SSL_VERIFY_FAIL_IF_NO_PEER_CERT = 2,
	SSL_VERIFY_CLIENT_ONCE = 4,

	SSL_SESS_CACHE_OFF = 30,
	SSL_SESS_CACHE_CLIENT = 31,
	SSL_SESS_CACHE_SERVER = 32,
	SSL_SESS_CACHE_BOTH = 33,
	SSL_SESS_CACHE_NO_AUTO_CLEAR = 34,
	SSL_SESS_CACHE_NO_INTERNAL_LOOKUP = 35,

	SSL_ERROR_WANT_READ = 2,
	SSL_ERROR_WANT_WRITE = 3,
	SSL_ERROR_WANT_CONNECT = 7,
	SSL_ERROR_WANT_ACCEPT = 8,
	SSL_ERROR_SYSCALL = 5,
	SSL_ERROR_WANT_X509_LOOKUP = 83,
	SSL_ERROR_ZERO_RETURN = 6,
	SSL_ERROR_SSL = 85,

	SSL_SENT_SHUTDOWN = 1,
	SSL_RECEIVED_SHUTDOWN = 2,
	SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER = 4,
	SSL_OP_NO_SSLv2 = 8,

	SSL_R_SSL_HANDSHAKE_FAILURE = 101,
	SSL_R_TLSV1_ALERT_UNKNOWN_CA = 102,
	SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN = 103,
	SSL_R_SSLV3_ALERT_BAD_CERTIFICATE = 104,

	PEM_BUFSIZE = 1024
};

int __cdecl client_hooks::InitSSL_CtxHook(int ctx, int a2) noexcept
{
	int result = InitSSL_CtxOg(ctx, a2);
	*(BYTE*)(ctx + 236) = 0; //verifyPeer
	*(BYTE*)(ctx + 237) = 1; // verifyNone

	return result;
}

int __cdecl client_hooks::setVerifyHook(int a1, int a2, int a3) noexcept
{
	console::Print("SET VERIFY %d", a2);
	return setVerifyOg(a1, SSL_VERIFY_NONE, a3);
}

int __cdecl client_hooks::connectSslHook(int* a1, int a2) noexcept
{
	int v6 = *a1;
	*(DWORD*)(v6 + 544) = 0; // verifyPeer

	int result = connectSslOg(a1, a2);
	return result;
}
