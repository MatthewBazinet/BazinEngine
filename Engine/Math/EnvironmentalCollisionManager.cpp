#include "EnvironmentalCollisionManager.h"
#include "..//Core/CoreEngine.h"

std::unique_ptr<EnvironmentalCollisionManager> EnvironmentalCollisionManager::environmentalCollisionInstance = nullptr;

std::vector<GameObject*> EnvironmentalCollisionManager::objects = std::vector<GameObject*>();
OctSpacialPartition* EnvironmentalCollisionManager::scenePartition = nullptr;

EnvironmentalCollisionManager::EnvironmentalCollisionManager()
{
	objects.reserve(10);
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
	objects.clear();
	scenePartition = new OctSpacialPartition(worldSize_);
}

void EnvironmentalCollisionManager::AddObject(GameObject* go_)
{
	if (scenePartition != nullptr)
	{
		scenePartition->AddObject(go_);
		objects.push_back(go_);
	}
}

void EnvironmentalCollisionManager::OnDestroy()
{
	for (auto entry : objects)
	{
		entry = nullptr;
	}
	objects.clear();
	delete scenePartition;
	scenePartition = nullptr;
}

void EnvironmentalCollisionManager::Update(GameObject* gameObject_, std::vector<glm::vec4> planes_)
{
	int i = 0;
	for (auto& element : planes_)
	{
		i++;
		if (checkPlaneCollision(gameObject_->GetPosition(), element))
		{
			std::cout << "Plane " << i << std::endl;
			if (element.x != 0.0f)
			{
				gameObject_->SetPosition(glm::vec3(-element.x * element.w - element.x * 0.1f, gameObject_->GetPosition().y, gameObject_->GetPosition().z));
			}
			else
			{
				gameObject_->SetPosition(glm::vec3(gameObject_->GetPosition().x, gameObject_->GetPosition().y, -element.z * element.w - element.z * 0.1f));
			}

			//gameObject_->GetPosition() + 0.1f * glm::vec3(-element.x, -element.y, -element.z);
			
			//std::cout << gameObject_->GetPosition().x << " " << gameObject_->GetPosition().z << std::endl;
			if (dynamic_cast<Character*>(gameObject_)) {
				if (dynamic_cast<Character*>(gameObject_)->getIsRunning())
				{
					dynamic_cast<Character*>(gameObject_)->SetIsRunning(false);
				}
			}
		}
	}

	checkObjectCollision(gameObject_);
}

//void EnvironmentalCollisionManager::Update(GameObject* gameObject_, glm::vec4 leftPlane_, glm::vec4 rightPlane_)
//{
//	if (checkPlaneCollision(gameObject_->GetHitBox()->getMaxVert(), leftPlane_))
//	{
//		gameObject_->SetVelocity(glm::vec3(-(leftPlane_.x), gameObject_->GetVelocity().y, gameObject_->GetVelocity().z));
//	}
//
//	if (checkPlaneCollision(gameObject_->GetHitBox()->getMaxVert(), rightPlane_))
//	{
//		std::cout << "collided" << std::endl;
//		gameObject_->SetVelocity(glm::vec3(-(rightPlane_.x), gameObject_->GetVelocity().y, gameObject_->GetVelocity().z));
//	}
//	checkObjectCollision(gameObject_);
//}

void EnvironmentalCollisionManager::checkObjectCollision(GameObject* gameObject_)
{
	for (auto gameObjects : objects)
	{
		if (gameObjects != gameObject_)
		{
			if (gameObject_->GetHitBox()->getMinVert().x - 1.0f <= gameObjects->GetHitBox()->getMaxVert().x + 1.0f && gameObject_->GetHitBox()->getMaxVert().x + 1.0f >= gameObjects->GetHitBox()->getMinVert().x - 1.0f/*, gameObject_->GetHitBox()->getMinVert().y <= gameObjects->GetHitBox()->getMaxVert().y && gameObject_->GetHitBox()->getMaxVert().y <= gameObjects->GetHitBox()->getMinVert().y, gameObject_->GetHitBox()->getMinVert().z >= gameObjects->GetHitBox()->getMaxVert().z && gameObject_->GetHitBox()->getMaxVert().z >= gameObjects->GetHitBox()->getMinVert().z*/)
			{
				// x collision
				if (gameObject_->GetHitBox()->getMinVert().x - 1.0f <= gameObjects->GetHitBox()->getMaxVert().x + 1.0f && gameObject_->GetPosition().y <= gameObjects->GetPosition().y + 2.0f)
				{
					gameObject_->SetVelocity(glm::vec3(-(gameObject_->GetVelocity().x), gameObject_->GetVelocity().y, gameObject_->GetVelocity().z));
				}
				else if(gameObject_->GetHitBox()->getMaxVert().x + 1.0f >= gameObjects->GetHitBox()->getMinVert().x - 1.0f && gameObject_->GetPosition().y <= gameObjects->GetPosition().y + 2.0f)
				{
					gameObject_->SetVelocity(glm::vec3(gameObject_->GetVelocity().x, gameObject_->GetVelocity().y, gameObject_->GetVelocity().z));
				}

				// z collision - doesnt work with running
				if (gameObject_->GetHitBox()->getMinVert().z - 1.0f <= gameObjects->GetHitBox()->getMaxVert().z + 1.0f && gameObject_->GetPosition().y <= gameObjects->GetPosition().y + 2.0f)
				{
					gameObject_->SetVelocity(glm::vec3(gameObject_->GetVelocity().x, gameObject_->GetVelocity().y, -gameObject_->GetVelocity().z));
					if (dynamic_cast<Character*>(gameObject_)) {
						if (dynamic_cast<Character*>(gameObject_)->getIsRunning())
						{
							dynamic_cast<Character*>(gameObject_)->SetIsRunning(false);
						}
					}
				}
				else if (gameObject_->GetHitBox()->getMaxVert().z + 1.0f >= gameObjects->GetHitBox()->getMinVert().z - 1.0f && gameObject_->GetPosition().y <= gameObjects->GetPosition().y + 2.0f)
				{
					gameObject_->SetVelocity(glm::vec3(gameObject_->GetVelocity().x, gameObject_->GetVelocity().y, gameObject_->GetVelocity().z));
					if (dynamic_cast<Character*>(gameObject_)) {
						if (dynamic_cast<Character*>(gameObject_)->getIsRunning())
						{
							dynamic_cast<Character*>(gameObject_)->SetIsRunning(false);
						}
					}
				}

				// y collision - not sure is needed?
				/*if (gameObject_->GetPosition().y <= gameObjects->GetPosition().y + 2.0f)
				{
					gameObject_->SetVelocity(glm::vec3(gameObject_->GetVelocity().x, +2.0f, gameObject_->GetVelocity().z));
				}*/
			}
		}
	}
}

bool EnvironmentalCollisionManager::checkPlaneCollision(glm::vec3 point_, glm::vec4 plane_)
{
	glm::vec4 tmpleftPlane = plane_;//NormalizePlane(plane_);
	float test = tmpleftPlane.x * point_.x + tmpleftPlane.y * point_.y + tmpleftPlane.z * point_.z + tmpleftPlane.w;
	
	if (test > -0.05f)
	{
			return false;
	}
	return true;
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