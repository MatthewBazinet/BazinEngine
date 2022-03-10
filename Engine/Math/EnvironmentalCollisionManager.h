#ifndef ENVIRONMENTALCOLLISIONMANAGER_H
#define ENVIRONMENTALCOLLISIONMANAGER_H

#include "../Engine/Rendering/3D/GameObject.h"
#include "../Game/Character.h"
#include "..//Core/OctSpatialPartition.h"
#include <vector>

class EnvironmentalCollisionManager
{
public:
	EnvironmentalCollisionManager(const EnvironmentalCollisionManager&) = delete;
	EnvironmentalCollisionManager(EnvironmentalCollisionManager&&) = delete;
	EnvironmentalCollisionManager* operator=(const EnvironmentalCollisionManager&) = delete;
	EnvironmentalCollisionManager* operator=(EnvironmentalCollisionManager&&) = delete;

	static EnvironmentalCollisionManager* GetInstance();
	void OnCreate(float worldSize_);
	void AddObject(GameObject* go_);
	void OnDestroy();
	void Update(GameObject* gameObject_, std::vector<glm::vec4> planes_);
	//void Update(GameObject* gameObject_, glm::vec4 leftPlane_, glm::vec4 rightPlane_);

	void checkObjectCollision(GameObject* gameObject_);
	bool checkPlaneCollision(glm::vec3 point_, glm::vec4 plane_);
	glm::vec4 NormalizePlane(glm::vec4 plane_);

private:
	EnvironmentalCollisionManager();
	~EnvironmentalCollisionManager();

	static std::unique_ptr<EnvironmentalCollisionManager> environmentalCollisionInstance;
	friend std::default_delete<EnvironmentalCollisionManager>;

	static std::vector<GameObject*> objects;
	static OctSpacialPartition* scenePartition;
};

#endif;