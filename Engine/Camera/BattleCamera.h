#ifndef BATTLECAMERA_H
#define BATTLECAMERA_H
#include "Camera.h"

class Character;

class BattleCamera :
	public Camera
{
public:
	BattleCamera();
	BattleCamera(float height_);
	~BattleCamera();
	void Update(const float deltaTime_);
	void SetPlayers(Character* player1_, Character* player2_);

	virtual void ProcessMouseMovement(glm::vec2 offset_);
	virtual void ProcessMouseZoom(int y_);
	
private:
	Character* player1;
	Character* player2;
	float height;
};

#endif