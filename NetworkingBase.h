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

	int Run(bool isServer);

};

#endif