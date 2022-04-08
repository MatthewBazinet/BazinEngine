#ifndef NIGHTGAUNT_H
#define NIGHTGAUNT_H

#include "Projectile.h"

class NightGaunt : public Projectile
{
public:
	NightGaunt(FrameData frameData_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~NightGaunt();
	void Update(const float deltaTime_);
private:
	FrameData frameData;
};

#endif NIGHTGAUNT_H