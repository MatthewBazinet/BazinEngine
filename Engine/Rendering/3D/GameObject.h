#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Model.h"
class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f,5.0f,5.0f,5.0f), glm::quat angularVelocity_ = glm::quat());
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const;
	glm::vec3 GetAccel() const;
	glm::vec3 GetVelocity() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;
	bool GetHit() const;

	float GetMaxSpeed()const;

	float GetMass() const;


	void ApplyForce(glm::vec3 force_);
	void SetPosition(glm::vec3 position_);
	void SetVelocity(glm::vec3 vel_);
	void SetAccel(glm::vec3 accel_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetOrientation(glm::quat orientation_);
	void SetAngularVelocity(glm::quat angularVelocity_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	void SetMaxSpeed(float maxSpeed_);

	void SetMass(float mass_);


private:
	Model* model;
	unsigned int modelInstance;

	glm::vec3 position;
	glm::vec3 vel;
	glm::vec3 accel;
	float maxSpeed;
	float mass;
	float angle;
	glm::vec3 rotation;
	glm::quat orientation;
	glm::quat angularVelocity;
	glm::vec3 scale;
	std::string tag;

	BoundingBox boundingBox;

	bool hit;
	bool intersects;

	void CheckVisible();
};

#endif //!GAMEOBJECT_H