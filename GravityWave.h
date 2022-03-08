#ifndef GRAVITYWAVE_H
#define GRAVITYWAVE_H

#include "Projectile.h"

class GravityWave : public Projectile
{
public:
	GravityWave(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, int strength_ = 0, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~GravityWave();
	void Update(float deltaTime_);
private:
	int strength;
};

#endif;