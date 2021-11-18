#ifndef NETWORKINGBASE_H
#define NETWORKINGBASE_H

#include <iostream>
#include <enet/enet.h>

class NetworkingBase
{
public:
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;
	static void SendPacket(ENetPeer* peer, const char* data);
	static int Run(bool isServer, char* hostIP);
	~NetworkingBase();

};

#endif