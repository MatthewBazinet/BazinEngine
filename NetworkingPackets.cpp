#include "NetworkingPackets.h"

NetworkingGameplayPacket::NetworkingGameplayPacket()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
	isRunning = false;
	isAirborne = false;
}

NetworkingGameplayPacket::~NetworkingGameplayPacket()
{
}
