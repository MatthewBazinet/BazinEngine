#ifndef BATTLECAMERA_H
#define BATTLECAMERA_H
#include "Camera.h"

class Character;

class BattleCamera :
	public Camera
{
public:
	BattleCamera();
	~BattleCamera();
	void Update(const float deltaTime_);
	void SetPlayers(Character* player1_, Character* player2_);
private:
	Character* player1;
	Character* player2;
};

#endif