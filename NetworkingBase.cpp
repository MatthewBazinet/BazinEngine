#include "NetworkingBase.h"
#include <thread>
#include "Engine/Core/CoreEngine.h"
#include "Game/Character.h"
#include <string>
#include <sstream>

bool NetworkingBase::isRunning = false;
bool NetworkingBase::connected = false;
bool NetworkingBase::isServer = false;
//ENetHost* NetworkingBase::client = nullptr;
//ENetPeer* NetworkingBase::peer = nullptr;

void NetworkingBase::MsgLoop(ENetHost* client, ENetEvent event, const char* name_) {
	while (isRunning) {
		while (enet_host_service(client, &event, 1000) > 0)
		{
			std::string packet;
			std::string second;
			std::string third;
			NetworkingGameplayPacket packetData = NetworkingGameplayPacket();
			switch (event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
					event.packet->dataLength,
					event.packet->data,
					event.peer->address.host,
					event.peer->address.port,
					event.channelID);
				packet = (char*)(event.packet->data);
				packetData = NetworkingGameplayPacket();
				packetData.x = std::stof(packet.substr(0, packet.find(' ')));
				second = packet.substr(packet.find(' ') + 1);
				packetData.y = std::stof(second.substr(0, second.find(' ')));
				third = second.substr(second.find(' ') + 1);
				packetData.z = std::stof(third.substr(0, third.find(' ')));
				dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(name_))->SetPosition(glm::vec3(packetData.x, packetData.y, packetData.z));

				//dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(name_))->SetRotation((*packet).rotation);


				/* Clean up the packet now that we're done using it. */
				//enet_packet_destroy(event.packet);
				//if(packet) delete packet;
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				/* Reset the peer's client information. */
				event.peer->data = NULL;
				break;
			}
		}
	}
}

void NetworkingBase::SendLoop(const char* name_)
{
	while (isRunning)
	{
		if (connected) {
			NetworkingGameplayPacket packet = NetworkingGameplayPacket();
			if (dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(name_))) {
				glm::vec3 pos = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(name_))->GetPosition();
				packet.x = pos.x;
				packet.y = pos.y;
				packet.z = pos.z;
				//packet.rotation = dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject(name_))->GetRotation();
				char serializedPacket[64 * 4];
				snprintf(serializedPacket, sizeof(serializedPacket), "%f %f %f", packet.x, packet.y, packet.z);
				if (peer) 
				{
					SendPacket(peer, serializedPacket);
					printf("Sent a packet\n");
				}
			}
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}
}
void NetworkingBase::SendPacket(ENetPeer* peer, const char* data)
{
	
	ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, 0);
	enet_peer_send(peer, 0, packet);
}

int NetworkingBase::Run(bool isServer,char* hostIP)
{
	NetworkingBase tmp;
	isRunning = true;
	NetworkingBase::isServer = isServer;

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
			connected = true;
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
		

		std::thread sendThread(&NetworkingBase::SendLoop, tmp, "char2");
		sendThread.detach();
		std::thread thread1(&NetworkingBase::MsgLoop, tmp, tmp.client,tmp.event, "char1");
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


		std::thread sendThread(&NetworkingBase::SendLoop, tmp, "char1");
		sendThread.detach();

		// gameloop
		while (isRunning)
		{
			ENetEvent event;
			/* Wait up to 1000 milliseconds for an event. */
			while (enet_host_service(tmp.client, &event, 1000) > 0)
			{
				std::string packet;
				std::string second;
				std::string third;
				NetworkingGameplayPacket packetData = NetworkingGameplayPacket();
				switch (event.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					printf("A new client connected from %x:%u.\n",
						event.peer->address.host,
						event.peer->address.port);
					tmp.peer = event.peer;
					CoreEngine::GetInstance()->SetCurrentScene(4);
					connected = true;
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					printf("A packet of length %u containing %s was received from %s on channel %u.\n",
						event.packet->dataLength,
						event.packet->data,
						event.peer->data,
						event.channelID);
					packet = (char*)(event.packet->data);
					packetData = NetworkingGameplayPacket();
					packetData.x = std::stof(packet.substr(0, packet.find(' ')));
					second = packet.substr(packet.find(' ') + 1);
					packetData.y = std::stof(second.substr(0, second.find(' ')));
					third = second.substr(second.find(' ') + 1);
					packetData.z = std::stof(third.substr(0, third.find(' ')));
					dynamic_cast<Character*>(SceneGraph::GetInstance()->GetGameObject("char2"))->SetPosition(glm::vec3(packetData.x, packetData.y, packetData.z));
					/* Clean up the packet now that we're done using it. */
					//enet_packet_destroy(event.packet);
					//if (packet) delete packet;
					/* Clean up the packet now that we're done using it. */
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("%s disconnected.\n", event.peer->data);
					/* Reset the peer's client information. */
					event.peer->data = NULL;
					break;
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