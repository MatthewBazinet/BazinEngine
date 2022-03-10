#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Model.h"
#include "../../../Tetrahedron.h"
#include "../Component.h"
#include "../Sphere.h"
#include "../Engine/Math/EnvironmentalHitBox.h"

class GameObject {
private:
	std::vector<Component*> components;
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), float angle_ = 0, glm::vec3 rotation_ = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat orientation_ = glm::quat(0.0f, 5.0f, 5.0f, 5.0f), glm::quat angularVelocity_ = glm::quat(), Tetrahedron shape = Tetrahedron());

	~GameObject();

	virtual void Update(const float deltaTime_);
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
	//float GetMaxAcceleration()const;
	float GetMass() const;
	Model* GetModel() const;
	std::vector<Mesh*> GetMeshes();
	int GetTargetNumber() const { return targetNumber; };
	glm::quat GetOrientation() const { return orientation; };
	

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
	void SetTargetNumber(int targetNumber_) { targetNumber = targetNumber_; };
	
	EnvironmentalHitBox* GetHitBox() { return eHitBox; };

	Tetrahedron GetShape();
	void SetShape(Tetrahedron shape_);

	template<typename ComponentTemplate, typename ... Args>
	void AddComponent(Args&& ... args_) {
		ComponentTemplate* comp = new ComponentTemplate(std::forward<Args>(args_)...);
		if (!dynamic_cast<Component*>(comp)) {
			///Trying to add a component that is not a base class of Component class
			delete comp;
			comp = nullptr;
			return;
		}
		if (GetComponent<ComponentTemplate>()) {
			///Trying to add a component type that is already added
			delete comp;
			comp = nullptr;
			return;
		}
		components.push_back(comp);
		comp->OnCreate(this);
	}

	template<typename ComponentTemplate>
	ComponentTemplate* GetComponent() {
		for (auto component : components) {
			if (dynamic_cast<ComponentTemplate*>(component)) {
				return dynamic_cast<ComponentTemplate*>(component);
			}
		}
		return nullptr;
	}

	template<typename ComponentTemplate>
	void RemoveComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (dynamic_cast<ComponentTemplate*>(components[i])) {
				delete components[i];
				components[i] = nullptr;
				components.erase(components.begin() + i);
				break;
			}
		}
	}


protected:
	Model* model;
	EnvironmentalHitBox* eHitBox;
	
	unsigned int modelInstance;

	glm::vec3 position;
	glm::vec3 vel;
	glm::vec3 accel;
	float maxSpeed;
	float maxAcceleration;
	float mass;
	float angle;
	glm::vec3 rotation;
	glm::quat orientation;
	glm::quat angularVelocity;
	glm::vec3 scale;
	std::string tag;

	int targetNumber;

	BoundingBox boundingBox;

	bool hit;
	bool intersects;

	void CheckVisible();

	Tetrahedron shape;
};

#endif //!GAMEOBJECT_H