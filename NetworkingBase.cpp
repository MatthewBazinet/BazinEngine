#include "NetworkingBase.h"
#include <thread>
#include "Engine/Core/CoreEngine.h"

void* MsgLoop(ENetHost* client, ENetEvent event) {
	while (true) {
		;
		while (enet_host_service(client, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->address.host,
					event.peer->address.port,
					event.channelID);
				break;
			}
		}
	}
}
void NetworkingBase::SendPacket(ENetPeer* peer, const char* data)
{
	
	ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

int NetworkingBase::Run(bool isServer,char* hostIP)
{
	NetworkingBase tmp;

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occured while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	tmp.client = enet_host_create(NULL, 1, 1, 0, 0);

	if (tmp.client == NULL)
	{
		fprintf(stderr, "An error occured creating the client.\n");
	}

	if (!isServer)
	{

		enet_address_set_host(&tmp.address,hostIP);
		tmp.address.port = 7777;

		tmp.peer = enet_host_connect(tmp.client, &tmp.address, 1, 0);
		if (tmp.peer == NULL)
		{
			fprintf(stderr, "No available peers for initiating a connection.");
			return EXIT_FAILURE;
		}

		if (enet_host_service(tmp.client, &tmp.event, 5000) > 0 && tmp.event.type == ENET_EVENT_TYPE_CONNECT)
		{
			puts("Connection to 127.0.0.1:7777 succeded.");
			CoreEngine::GetInstance()->SetCurrentScene(4);
		}
		else
		{
			enet_peer_reset(tmp.peer);
			puts("Connection failed.");
			return EXIT_FAILURE;
		}

		/*
		while (enet_host_service(tmp.client, &tmp.event, 1000) > 0)
		{
			switch (tmp.event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
					tmp.event.packet->dataLength,
					tmp.event.packet->data,
					tmp.event.peer->address.host,
					tmp.event.peer->address.port,
					tmp.event.channelID);
				break;
			}
		}*/
		SendPacket(tmp.peer, "this is a packet");


		std::thread thread1(MsgLoop, tmp.client,tmp.event);
		thread1.join();



		enet_peer_disconnect(tmp.peer, 0);

		while (enet_host_service(tmp.client, &tmp.event, 3000) > 0)
		{
			switch (tmp.event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(tmp.event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				puts("Disconnection succeeded.");
				break;
			}
		}

		return EXIT_SUCCESS;
	}
	else
	{
		/* Bind the server to the default localhost.     */
/* A specific host address can be specified by   */
/* enet_address_set_host (& address, "x.x.x.x"); */
		tmp.address.host = ENET_HOST_ANY; // This allows
		/* Bind the server to port 7777. */
		tmp.address.port = 7777;



		tmp.client = enet_host_create(&tmp.address	/* the address to bind the server host to */,
			32	/* allow up to 32 clients and/or outgoing connections */,
			1	/* allow up to 1 channel to be used, 0. */,
			0	/* assume any amount of incoming bandwidth */,
			0	/* assume any amount of outgoing bandwidth */);

		if (tmp.client == NULL)
		{
			printf("An error occurred while trying to create an ENet server host.");
			return 1;
		}

		// gameloop
		while (true)
		{
			ENetEvent event;
			/* Wait up to 1000 milliseconds for an event. */
			while (enet_host_service(tmp.client, &event, 1000) > 0)
			{
				switch (event.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					printf("A new client connected from %x:%u.\n",
						event.peer->address.host,
						event.peer->address.port);
					CoreEngine::GetInstance()->SetCurrentScene(4);
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					printf("A packet of length %u containing %s was received from %s on channel %u.\n",
						event.packet->dataLength,
						event.packet->data,
						event.peer->data,
						event.channelID);
					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy(event.packet);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("%s disconnected.\n", event.peer->data);
					/* Reset the peer's client information. */
					event.peer->data = NULL;
				}
			}
		}

		enet_host_destroy(tmp.client);
		
		return 0;
	}
}

NetworkingBase::~NetworkingBase()
{
	delete client;
	client = nullptr;

	delete peer;
	peer = nullptr;
}