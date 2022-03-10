#ifndef KUNAI_H
#define KUNAI_H

#include "Projectile.h"

class Kunai : public Projectile
{
public:
	Kunai(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Kunai();
	void Update(float deltaTime_);
};

#endif;