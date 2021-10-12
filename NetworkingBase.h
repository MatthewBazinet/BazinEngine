#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string>

// Force asserts to be enabled, even in release build
#undef NDEBUG
#ifndef _DEBUG
#define _DEBUG
#endif
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#include <GameNetworkingSockets/steam/steamnetworkingsockets.h>
#include <GameNetworkingSockets/steam/isteamnetworkingsockets.h>


class NetworkingBase
{
	void CreateIdentities() {
		SteamNetworkingIdentity identityLocal;
		//identityLocal.Clear();
		SteamNetworkingIdentity identityRemote;
		//identityRemote.Clear();
		//const char* pszTrivialSignalingService = "localhost:10000";
	}

};
