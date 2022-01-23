#include "EnvironmentalCollisionManager.h"
#include "..//Core/CoreEngine.h"

std::unique_ptr<EnvironmentalCollisionManager> EnvironmentalCollisionManager::environmentalCollisionInstance = nullptr;

std::vector<GameObject*> EnvironmentalCollisionManager::prevCollisions = std::vector<GameObject*>();
OctSpacialPartition* EnvironmentalCollisionManager::scenePartition = nullptr;

EnvironmentalCollisionManager::EnvironmentalCollisionManager()
{
	prevCollisions.reserve(10);
}

EnvironmentalCollisionManager::~EnvironmentalCollisionManager()
{
	OnDestroy();
}

EnvironmentalCollisionManager* EnvironmentalCollisionManager::GetInstance()
{
	if (environmentalCollisionInstance.get() == nullptr)
	{
		environmentalCollisionInstance.reset(new EnvironmentalCollisionManager);
	}
	return environmentalCollisionInstance.get();
}

void EnvironmentalCollisionManager::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	scenePartition = new OctSpacialPartition(worldSize_);
}

void EnvironmentalCollisionManager::AddObject(GameObject* go_)
{
	if (scenePartition != nullptr)
	{
		scenePartition->AddObject(go_);
	}
}

void EnvironmentalCollisionManager::OnDestroy()
{
	for (auto entry : prevCollisions)
	{
		entry = nullptr;
	}
	prevCollisions.clear();
	delete scenePartition;
	scenePartition = nullptr;
}

bool EnvironmentalCollisionManager::checkPlaneCollision(glm::vec3 point_, glm::vec4 plane_)
{
	glm::vec4 tmpleftPlane = NormalizePlane(plane_);
	float test = tmpleftPlane.x * point_.x + tmpleftPlane.y * point_.y + tmpleftPlane.z * point_.z + tmpleftPlane.w;

	//std::cout << test << std::endl;

	if (test < -0.05f) {
		return false;
	};
}

glm::vec4 EnvironmentalCollisionManager::NormalizePlane(glm::vec4 plane_)
{
	glm::vec4 Result = plane_;

	float Distance = sqrtf(plane_.x * plane_.x + plane_.y * plane_.y + plane_.z * plane_.z);
	Result.x = plane_.x / Distance;
	Result.y = plane_.y / Distance;
	Result.z = plane_.z / Distance;
	Result.w = plane_.w / Distance;

	return Result;
}