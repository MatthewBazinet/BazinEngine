#ifndef NETWORKINGPACKETS_H
#define NETWORKINGPACKETS_H
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

struct NetworkingMatchStartPacket
{
	int character;
	int skin;
	int stage;
	std::string name;
};

struct NetworkingGameplayPacket
{
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::quat orientation;
	bool isRunning;
	bool isAirborne;
};

#endif // !NETWORKINGPACKETS_H