
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Engine/Rendering/3D/GameObject.h"
#include "..//Engine/Camera/BattleCamera.h"

#include <unordered_map>
#include "..//MorphTarget.h"
#include "..//MorphTargetAnimatedModel.h"


enum class moveState {NONE, RUN, GROUNDLIGHT, GROUNDMEDIUM, GROUNDHEAVY, AIRLIGHT, AIRMEDIUM, AIRHEAVY, QCF, QCB, UNIQUE};

class Projectile;
class HurtBox;
class HitBox;

struct FrameData
{
	FrameData();
	~FrameData();
	float GetTotalTime();
	float startup;
	float active;
	float recovery;
	float damage;
	float hitStun;
	float blockStun;
	glm::vec3 push;
};

class Character : public GameObject
{
public:

	Character(float health_, float meter_, bool isRunning_, bool isAirborne_, Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0.0f, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat());
	~Character();

	void NotifyOnKeyDown(SDL_Scancode key_);
	void NotifyOnKeyUp(SDL_Scancode key_);

	virtual void Update(const float deltaTime_);

	virtual void QCF(int strength, bool simpleInput);
	virtual void QCB(int strength, bool simpleInput);
	virtual void Unique();
	virtual void Light();
	virtual void Medium();
	virtual void Heavy();
	virtual void Run(bool isRunning_);
	virtual void Move(glm::vec2 input);
	virtual void OnLand();

	void Hit(float damage_, float hitStun_, float blockStun_, glm::vec3 push_);
	void Hit(FrameData frameData_);

	bool getIsRunning() const { return isRunning; };
	bool getIsAirborne() const { return isAirborne; };

	void SetIsRunning(bool isRunning_) { isRunning = isRunning_; if (!isRunning) relativeVel = glm::vec3(0.0f, 0.0f, 0.0f); };

	void SetOpponent(Character* opponent_) { opponent = opponent_; };
	void SetCamera(Camera* camera_) { camera = camera_; };
	//void SetProjectile(Projectile* projectile_) { proj = projectile_; };

	Character* GetOpponent()const { return opponent; };
	float GetHealth() const { return health; };
	void SetHealth(float health_) { health = health_; };
	float GetOverclock() const { return overclock; };
	void SetOverclock(float overclock_) { overclock = overclock_; };
	std::vector<Sphere> GetHurtBoxes()const;
	bool IsCharge();
	bool FacingLeft();

	bool CheckMoveState(moveState move_);
	bool CheckRunCancel();
	void resetCombo();
	bool checkComboState(moveState move_);

	bool getApplyGravity() const { return applyGravity; };
	void setApplyGravity(bool applyGravity_) { applyGravity = applyGravity_; };

protected:

	std::unordered_map<std::string, HitBox*> hitBoxes;
	std::unordered_map<std::string, HurtBox*> hurtBoxes;
	std::unordered_map<std::string, FrameData> frameData;
	std::unordered_map<std::string, int> combo = { {"light", 1}, {"medium", 1}, {"heavy", 1} };

	virtual void AirQCF(int strength, bool simpleInput);
	virtual void AirQCB(int strength, bool simpleInput);
	virtual void AirUnique();
	virtual void AirLight();
	virtual void AirMedium();
	virtual void AirHeavy();

	void SetFrameData(float startup_, float active_, float recovery_);
	void SetFrameData(FrameData frameData_);

	virtual void OnDeath();

	float health;
	float overclock;
	float nextActionable;

	float moveTimeLeft;
	float startUpTimeLeft;
	float activeTimeLeft;
	float recoveryTimeLeft;

	FrameData currentFrameData;
	
	bool isRunning;
	bool isAirborne;
	bool isAttacking;
	bool isIdle;
	bool applyGravity;
	Model* model;
	//Projectile* proj;
	Character* opponent;

	Camera* camera;
	glm::vec3 axisOf2DMovement;
	float dir2D;
	bool MovingLeft;
	bool MovingRight;
	glm::vec3 target;

	glm::vec3 relativeVel;
	HurtBox* hurtBox;
	HitBox* hitBox;

	bool isCharge;
	moveState currentMove;

	glm::vec2 lastInput;
};

#endif