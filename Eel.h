#ifndef EEL_H
#define EEL_H

#include "Projectile.h"
class Eel : public Projectile
{
public:
	Eel(FrameData frameData_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(0.2f, 0.2f, 0.2f));
	~Eel();
	void Update(const float deltaTime_);
private:
	FrameData frameData;
};

#endif;