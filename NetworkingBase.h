#ifndef NETWORKINGBASE_H
#define NETWORKINGBASE_H

#include <iostream>
#include <enet/enet.h>
#include "NetworkingPackets.h"

class NetworkingBase
{
public:
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;
	static void SendPacket(ENetPeer* peer, const char* data);
	static int Run(bool isServer, char* hostIP);
	void MsgLoop(ENetHost* client, ENetEvent event, const char* name_);
	void SendLoop(const char* name_);
	~NetworkingBase();
	static bool isRunning;
	static bool connected;
	static bool isServer;
};

#endif