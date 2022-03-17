#include "HitBox.h"
#include "Engine/Math/CollisionDetection.h"
#include <glm/gtx/rotate_vector.hpp>
HitBox::HitBox(Model* model_, glm::vec3 position_, GameObject* parent_, float angle_, glm::vec3 rotation_, glm::vec3 scale_, glm::vec3 vel_, glm::quat orientation_, glm::quat angularVelocity_) : GameObject(model_, position_, angle_, rotation_, scale_, vel_, orientation_, angularVelocity_)
{
	parent = parent_;
	isEnabled = true;
	int j = 0;
}


HitBox::~HitBox()
{
	if (hitBoxVisual.size() > 0)
	{
		for (auto m : hitBoxVisual)
		{
			SceneGraph::GetInstance()->RemoveGameObject(m->GetTag());
			m = nullptr;
		}
		hitBoxVisual.clear();
	}
}


bool HitBox::CheckCollision(HitBox* hitbox)
{
	if (isEnabled) {
		if ((this->minVert.x <= hitbox->maxVert.x && this->maxVert.x >= hitbox->minVert.x) && (this->minVert.y <= hitbox->maxVert.y && this->maxVert.y >= hitbox->minVert.y) && (this->minVert.z <= hitbox->maxVert.z && this->maxVert.z >= hitbox->minVert.z))
		{
			//std::cout << "collided" << std::endl;
			return true;
		}
	}

	return false;
}

bool HitBox::CheckCollision(std::vector<Sphere> hurtbox)
{
	if (isEnabled) {
		for (int i = 0; i < hurtbox.size(); i++) {
			for (int j = 0; j < hitBoxes.size(); j++) {
				if (CollisionDetection::SphereSphereCollision(hurtbox[i], hitBoxes[j]))
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<Sphere> HitBox::spawnSpheres(glm::vec3 startingPos_, glm::vec3 endingPos_, float width_, int numOfSpheres)
{
	HurtBoxVisual* hurtBoxDebug = new HurtBoxVisual("Resources/Models/Sphere.obj", "Resources/Materials/tetrahedron.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"), false);
	SceneGraph::GetInstance()->AddModel(hurtBoxDebug);
	if (numOfSpheres >= 2) {
		float dist = glm::distance(startingPos_, endingPos_);
		float spacing = dist / numOfSpheres;
		
		for (int i = 0; i < numOfSpheres; i++) {
			glm::vec3 pos = GetPointOnLine(startingPos_, endingPos_, i * spacing / dist);
			hitBoxes.push_back(Sphere(pos, width_));
			SceneGraph::GetInstance()->AddGameObject(new HurtBox(hurtBoxDebug, pos, parent), "Hitbox " + std::to_string(i));
			hitBoxVisual.push_back(SceneGraph::GetInstance()->GetGameObject("Hitbox " + std::to_string(i)));
			hitBoxVisual[i]->SetScale(glm::vec3(width_));
			hitBoxes[i].SetOffset(hitBoxes[i].position- parent->GetPosition());
		}
		return hitBoxes;
	}
	else {
		spheres.resize(numOfSpheres);
		spheres[0] = Sphere(startingPos_, width_);
		hitBoxes.push_back(spheres[0]);
		SceneGraph::GetInstance()->AddGameObject(new HurtBox(hurtBoxDebug, startingPos_, parent),"ProjectileHB");
		hitBoxVisual.push_back(SceneGraph::GetInstance()->GetGameObject("ProjectileHB"));
		hitBoxVisual[0]->SetScale(glm::vec3(width_));
		//std::cout << hitBoxes[0].position.x << "," << hitBoxes[0].position.y << "," << hitBoxes[0].position.z << std::endl;
		return hitBoxes;
	}

	return std::vector<Sphere>();
}
glm::vec3 HitBox::GetPointOnLine(glm::vec3 x, glm::vec3 y, float normalizedDistance)
{
	return x + (y - x) * normalizedDistance;
}
void HitBox::Update(float deltaTime_)
{
	if (parent) {
		for (int i = 0; i < hitBoxes.size(); i++) {
			hitBoxes[0].SetPosition(parent->GetPosition());
			hitBoxVisual[0]->SetPosition(parent->GetPosition());
			if (i != 0) {
				bool left = dynamic_cast<Character*>(parent)->FacingLeft();
				if (left)
				{
					hitBoxes[i].SetPosition(glm::vec3(parent->GetPosition() + glm::rotate(hitBoxes[i].offset, -glm::radians(CoreEngine::GetInstance()->GetCamera()->GetRotation().x + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
				}
				else
				{
					hitBoxes[i].SetPosition(glm::vec3(parent->GetPosition() + glm::rotate(hitBoxes[i].offset, -glm::radians(CoreEngine::GetInstance()->GetCamera()->GetRotation().x - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
				}
				hitBoxVisual[i]->SetPosition(hitBoxes[i].position);
			}
		}
		GameObject::Update(deltaTime_);
	}
}
