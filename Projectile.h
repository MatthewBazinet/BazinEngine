#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Engine/Rendering/3D/GameObject.h"
#include "KinematicSeek.h"
#include "MatchVelocity.h"
#include "HitBox.h"
#include "Engine/Math/CollisionHandler.h"
#include "Game/Character.h"

class Projectile : public GameObject
{
	
private:
	GameObject* target;
	HitBox* hitBox;
	Character* parent;
public:
	void Update(const float deltaTime_) override;
	Projectile(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), Character* parent_  = nullptr, float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Projectile();
	void SetTarget(GameObject* target_) { target = target_; };
	void Separate(std::vector<GameObject*> objects_);

};
#endif
