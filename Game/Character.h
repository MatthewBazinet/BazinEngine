
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Engine/Rendering/3D/GameObject.h"
#include "..//Engine/Camera/BattleCamera.h"
#include "../Projectile.h"
#include <unordered_map>
#include "..//MorphTarget.h"
#include "..//MorphTargetAnimatedModel.h"
class Character : public GameObject
{
public:

	Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0.0f, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Character();

	void NotifyOnKeyDown(SDL_Scancode key_);
	void NotifyOnKeyUp(SDL_Scancode key_);

	virtual void Update(const float deltaTime_);

	void ReadInput();

	void QCF(int strength, bool simpleInput);
	void QCB(int strength, bool simpleInput);
	void Unique();
	void Light();
	void Medium();
	void Heavy();
	void Run(bool isRunning_);
	void Move(glm::vec2 input);

	bool getIsRunning() const { return isRunning; };
	bool getIsAirborne() const { return isAirborne; };

	void SetOpponent(Character* opponent_) { opponent = opponent_; };
	void SetCamera(Camera* camera_) { camera = camera_; };
	void SetProjectile(Projectile* projectile_) { proj = projectile_; };

	float GetHealth() const { return health; };

protected:

	void AirQCF(int strength, bool simpleInput);
	void AirQCB(int strength, bool simpleInput);
	void AirUnique();
	void AirLight();
	void AirMedium();
	void AirHeavy();

	float health;
	float overclock;
	float nextActionable;
	
	bool isRunning;
	bool isAirborne;
	Model* model;
	Projectile* proj;
	Character* opponent;

	Camera* camera;
	glm::vec3 axisOf2DMovement;
	float dir2D;
	bool MovingLeft;
	bool MovingRight;
	glm::vec3 target;

	glm::vec3 relativeVel;

};

#endif