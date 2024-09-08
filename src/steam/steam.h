#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include <mutex>

#define STEAM_EXPORT extern "C" __declspec(dllexport)

// This was taken from https://github.com/iw4x/iw4x-client/blob/develop/src/Steam/Steam.hpp
// Modified to fit the game
// All credits to the iw4x team

#include "interfaces/steam_apps.h"
#include "interfaces/steam_client.h"
#include "interfaces/steam_friends.h"
#include "interfaces/steam_matchmaking.h"
#include "interfaces/steam_matchmakingservers.h"
#include "interfaces/steam_networking.h"
#include "interfaces/steam_user.h"
#include "interfaces/steam_userstats.h"
#include "interfaces/steam_utils.h"

namespace steam
{
	class Callbacks
	{
	public:
		class Base
		{
		public:
			Base() : Flags(0), Callback(0) {};

			virtual void Run(void* pvParam) = 0;
			virtual void Run(void* pvParam, bool bIOFailure, uint64_t hSteamAPICall) = 0;
			virtual int GetCallbackSizeBytes() = 0;

			int GetICallback() { return Callback; }
			void SetICallback(int iCallback) { Callback = iCallback; }

		protected:
			~Base() = default;

			unsigned char Flags;
			int Callback;
		};

		struct Result
		{
			void* data;
			int size;
			int type;
			uint64_t call;
		};

		static uint64_t RegisterCall();
		static void RegisterCallback(Base* handler, int callback);
		static void RegisterCallResult(uint64_t call, Base* result);
		static void ReturnCall(void* data, int size, int type, uint64_t call);
		static void RunCallbacks();

		static void RunCallback(int32_t callback, void* data);

		static void Uninitialize();

	private:
		static uint64_t CallID;
		static std::map<uint64_t, bool> Calls;
		static std::map<uint64_t, Base*> ResultHandlers;
		static std::vector<Result> Results;
		static std::vector<Base*> CallbackList;
		static std::recursive_mutex Mutex;
	};


	STEAM_EXPORT bool SteamAPI_Init();
	STEAM_EXPORT bool SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID);
	STEAM_EXPORT void SteamAPI_UnregisterCallback();
	STEAM_EXPORT void SteamAPI_RegisterCallback(Callbacks::Base* handler, int callback);
	STEAM_EXPORT void SteamAPI_RunCallbacks();
	STEAM_EXPORT void SteamAPI_Shutdown();
	STEAM_EXPORT void SteamAPI_SetMiniDumpComment(const char* pchMsg);
	STEAM_EXPORT void SteamAPI_UnregisterCallResult();
	STEAM_EXPORT void SteamAPI_RegisterCallResult(Callbacks::Base* result, uint64_t call);
	STEAM_EXPORT bool SteamAPI_RestartAppIfNecessary();

	STEAM_EXPORT steam::apps SteamApps();
	STEAM_EXPORT steam::client SteamClient();
	STEAM_EXPORT steam::friends SteamFriends();
	STEAM_EXPORT steam::matchmaking SteamMatchmaking();
	STEAM_EXPORT steam::matchmakingservers SteamMatchmakingServers();
	STEAM_EXPORT steam::networking SteamNetworking();
	STEAM_EXPORT steam::user SteamUser();
	STEAM_EXPORT steam::userstats SteamUserStats();
	STEAM_EXPORT steam::utils SteamUtils();
}