#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f,1.0f,1.0f), glm::vec3 vel_ = glm::vec3(0.0f,0.0f,0.0f));
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	std::string GetTag() const;
	BoundingBox GetBoundingBox() const;
	bool GetHit() const;

	void ApplyForce(glm::vec3 force_);
	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

private:
	Model* model;
	unsigned int modelInstance;

	glm::vec3 position;
	glm::vec3 vel;
	glm::vec3 accel;
	float mass;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::string tag;

	BoundingBox boundingBox;

	bool hit;

	void CheckVisible();
};

#endif //!GAMEOBJECT_H