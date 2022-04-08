#ifndef SPIKE_H
#define SPIKE_H

#include "Projectile.h"
class Spike : public Projectile
{
public:
	Spike(FrameData frameData_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_ = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f));
	~Spike();
	void Update(const float deltaTime_);
	void SetActive(bool active_) { active = active_; };

private:
	FrameData frameData;
	bool active;
	bool modelLoaded;
	float lifetime;
	float time;
};

#endif;