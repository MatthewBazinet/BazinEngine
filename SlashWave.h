#ifndef SLASHWAVE_H
#define SLASHWAVE_H

#include "Projectile.h"

class SlashWave : public Projectile
{
public:
	SlashWave(FrameData frameData_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~SlashWave();
	void Update(float deltaTime_);
	FrameData frameData;
};

#endif;