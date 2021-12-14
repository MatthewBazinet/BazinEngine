#ifndef NETWORKINGPACKETS_H
#define NETWORKINGPACKETS_H
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

struct Packet
{

};

struct NetworkingMatchStartPacket : public Packet
{
	int character;
	int skin;
	int stage;
	std::string name;
};

struct NetworkingGameplayPacket : public Packet
{
	NetworkingGameplayPacket();
	~NetworkingGameplayPacket();
	float x;
	float y;
	float z;
	float pitch;
	float yaw;
	float roll;
	bool isRunning;
	bool isAirborne;
};

#endif // !NETWORKINGPACKETS_H